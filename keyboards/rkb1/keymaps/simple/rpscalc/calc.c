#include "calc.h"
#include <math.h>
#include <quantum.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct StackElement {
    double               x;
    int                  ent_len;
    struct StackElement *next;
};

enum NumberReadState {
    NUMBER_READ_STATE_INITIAL,
    NUMBER_READ_STATE_PREDECIMAL,
    NUMBER_READ_STATE_DECIMAL,
    NUMBER_READ_STATE_EXPONENT_INIT,
    NUMBER_READ_STATE_EXPONENT,
};

static double               read_number = 0.0, number_multiplier = 1.0;
static int                  exponent = 0, exponent_sign = 1, charsRead = 0;
static enum NumberReadState number_read_state = NUMBER_READ_STATE_INITIAL;
static struct StackElement *number_stack      = NULL;

static void pushNoPrint(double x, int ent_len) {
    struct StackElement *buf = malloc(sizeof(struct StackElement));
    buf->x                   = x;
    buf->ent_len             = ent_len;
    buf->next                = number_stack;
    number_stack             = buf;
}

static void push(double x) {
    char buf[32];
    memset(buf, 0, sizeof(buf));
    int real_length = snprintf(buf, sizeof(buf), "%.16g", x);
    send_unicode_string(buf);
    send_unicode_string(" ");
    pushNoPrint(x, real_length);
}

static int pop_(double *x, int *ent_len) {
    struct StackElement *buf = number_stack;
    if (buf == NULL) {
        return 0;
    }

    *x           = buf->x;
    *ent_len     = buf->ent_len;
    number_stack = buf->next;
    free(buf);
    return 1;
}

static void backspace(void) {
    tap_code(KC_BACKSPACE);
}

static void backspace_n(int n) {
    for (int i = 0; i < n; i++) {
        backspace();
    }
}

static int pop(double *x) {
    int ent_len;
    if (pop_(x, &ent_len)) {
        backspace_n(ent_len + 1);
        return 1;
    }
    return 0;
}

static void reset_number_parser(void) {
    read_number       = 0.0;
    number_multiplier = 1.0;
    exponent          = 0;
    exponent_sign     = 1;
    number_read_state = NUMBER_READ_STATE_INITIAL;
    charsRead         = 0;
}

static int parse_number_char(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

static int parse_number_step(char c) {
    if (number_read_state == NUMBER_READ_STATE_INITIAL) {
        number_read_state = NUMBER_READ_STATE_PREDECIMAL;
        if (c == '-') number_multiplier *= -1.0;
        if (c == '+' || c == '-') return 0;
    }

    if (number_read_state == NUMBER_READ_STATE_PREDECIMAL && c == '.') {
        number_read_state = NUMBER_READ_STATE_DECIMAL;
        return 0;
    }

    if (number_read_state < NUMBER_READ_STATE_EXPONENT_INIT) {
        if (c == 'e' || c == 'E') {
            number_read_state = NUMBER_READ_STATE_EXPONENT_INIT;
            return 0;
        }
        int parsed_number = parse_number_char(c);
        if (parsed_number == -1) return -1;
        read_number *= 10.0;
        read_number += parsed_number;
        if (number_read_state == NUMBER_READ_STATE_DECIMAL) number_multiplier /= 10.0;
        return 0;
    }

    if (number_read_state == NUMBER_READ_STATE_EXPONENT_INIT) {
        number_read_state = NUMBER_READ_STATE_EXPONENT;
        if (c == '-') exponent_sign *= -1;
        if (c == '+' || c == '-') return 0;
    }
    int parsed_number = parse_number_char(c);
    if (parsed_number == -1) return -1;
    exponent *= 10;
    exponent += parsed_number;
    return 0;
}

static void finish_number(void) {
    double result = read_number * number_multiplier * pow(10.0, exponent * exponent_sign);
    pushNoPrint(result, charsRead);
    reset_number_parser();
}

static int parse_number(char c) {
    charsRead++;
    if (!parse_number_step(c)) {
        return 1;
    }
    finish_number();
    return 0;
}

static char enabled = 0;

#define def_primop(name, op)       \
    static void run_##name(void) { \
        double a, b;               \
        backspace();               \
        if (!pop(&b)) return;      \
        if (!pop(&a)) return;      \
        push(a op b);              \
    }

def_primop(add, +);
def_primop(sub, -);
def_primop(mul, *);
def_primop(div, /);

static void run_swap(void) {
    double a, b;
    backspace();
    if (!pop(&b)) return;
    if (!pop(&a)) return;
    push(a);
    push(b);
}

#define def_unop(name)             \
    static void run_##name(void) { \
        double a;                  \
        if (!pop(&a)) return;      \
        push((name)(a));           \
    }

#define def_binop(name)            \
    static void run_##name(void) { \
        double a, b;               \
        if (!pop(&b)) return;      \
        if (!pop(&a)) return;      \
        push((name)(a, b));        \
    }

def_unop(acos);
def_unop(acosh);
def_unop(asin);
def_unop(asinh);
def_unop(atan);
def_binop(atan2);
def_unop(atanh);
def_unop(cbrt);
def_unop(ceil);
def_binop(copysign);
def_unop(cos);
def_unop(cosh);
def_unop(erf);
def_unop(erfc);
def_unop(exp);
def_unop(exp2);
def_unop(expm1);
def_unop(fabs);
def_binop(fdim);
def_unop(floor);
static void run_fma(void) {
    double a, b, c;
    if (!pop(&c)) return;
    if (!pop(&b)) return;
    if (!pop(&a)) return;
    push(fma(a, b, c));
}
def_binop(fmax);
def_binop(fmin);
def_binop(fmod);
static void run_frexp(void) {
    double a;
    int    b;
    if (!pop(&a)) return;
    a = frexp(a, &b);
    push(a);
    push(b);
}
def_binop(hypot);
def_unop(ilogb);
def_binop(ldexp);
def_unop(lgamma);
def_unop(log);
def_unop(log10);
def_unop(log1p);
def_unop(log2);
def_unop(logb);
static void run_modf(void) {
    double a, b;
    if (!pop(&a)) return;
    a = modf(a, &b);
    push(a);
    push(b);
}
def_unop(nearbyint);
def_binop(nextafter);
def_binop(pow);
def_binop(remainder);
static void run_remquo(void) {
    double a, b;
    int    c;
    if (!pop(&a)) return;
    if (!pop(&b)) return;
    a = remquo(a, b, &c);
    push(a);
    push(c);
}
def_unop(rint);
def_unop(round);
static void run_scalbn(void) {
    double a, b;
    if (!pop(&a)) return;
    if (!pop(&b)) return;
    push(scalbn(a, (int)b));
}
def_unop(sin);
def_unop(sinh);
def_unop(sqrt);
def_unop(tan);
def_unop(tanh);
def_unop(tgamma);
def_unop(trunc);

#define def_constop(name, constant) \
    static void run_##name(void) {  \
        push(constant);             \
    }

def_constop(EPSILON, 2.2204460492503131E-16);
def_constop(MIN, -1.7976931348623157E+308);
def_constop(MIN_POSITIVE, 2.2250738585072014E-308);
def_constop(MAX, 1.7976931348623157E+308);
def_constop(NAN, NAN);
def_constop(INFINITY, INFINITY);
def_constop(NEG_INFINITY, -INFINITY);
def_constop(E, 2.71828182845904523536028747135266250);
def_constop(FRAC_1_PI, 0.318309886183790671537767526745028724);
def_constop(FRAC_1_SQRT_2, 0.707106781186547524400844362104849039);
def_constop(FRAC_2_PI, 0.636619772367581343075535053490057448);
def_constop(FRAC_2_SQRT_PI, 1.12837916709551257389615890312154517);
def_constop(FRAC_PI_2, 1.57079632679489661923132169163975144);
def_constop(FRAC_PI_3, 1.04719755119659774615421446109316763);
def_constop(FRAC_PI_4, 0.785398163397448309615660845819875721);
def_constop(FRAC_PI_6, 0.52359877559829887307710723054658381);
def_constop(FRAC_PI_8, 0.39269908169872415480783042290993786);
def_constop(LN_2, 0.693147180559945309417232121458176568);
def_constop(LN_10, 2.30258509299404568401799145468436421);
def_constop(LOG2_10, 3.32192809488736234787031942948939018);
def_constop(LOG2_E, 1.44269504088896340735992468100189214);
def_constop(LOG10_2, 0.301029995663981195213738894724493027);
def_constop(LOG10_E, 0.434294481903251827651128918916605082);
def_constop(PI, 3.14159265358979323846264338327950288);
def_constop(SQRT_2, 1.41421356237309504880168872420969808);
def_constop(TAU, 6.28318530717958647692528676655900577);

void calculator_enable(void) {
    enabled = 1;
}

int calculator_is_active(void) {
    return enabled;
}

static char fn_buf[17];
int         fn_pos = 0;

static void reset_fn_buf_state(void) {
    memset(fn_buf, 0, sizeof(fn_buf));
    fn_pos = 0;
}

void calculator_process_backspace(void) {
    double x;
    if (number_read_state != NUMBER_READ_STATE_INITIAL) {
        finish_number();
    }
    if (fn_pos > 0) {
        backspace_n(fn_pos);
    } else if (!pop(&x)) {
        calculator_disable();
    }
}

void calculator_disable(void) {
    double x;
    int    ent_len;
    enabled = 0;
    if (number_read_state != NUMBER_READ_STATE_INITIAL) {
        finish_number();
    }
    while (pop_(&x, &ent_len))
        ;
    reset_fn_buf_state();
}

static void try_run_op(void) {
    backspace_n(fn_pos + 1);
    // Why do kmp when you can do this?
#define CASE(name) else if (strcmp(fn_buf, #name) == 0) run_##name();
    if (0) {
    }
    CASE(acosh)
    CASE(acos)
    CASE(asinh)
    CASE(asin)
    CASE(atanh)
    CASE(atan2)
    CASE(atan)
    CASE(cbrt)
    CASE(ceil)
    CASE(copysign)
    CASE(cosh)
    CASE(cos)
    CASE(erfc)
    CASE(erf)
    CASE(exp2)
    CASE(expm1)
    CASE(exp)
    CASE(fabs)
    CASE(fdim)
    CASE(floor)
    CASE(fma)
    CASE(fmax)
    CASE(fmin)
    CASE(fmod)
    CASE(frexp)
    CASE(hypot)
    CASE(ilogb)
    CASE(ldexp)
    CASE(lgamma)
    CASE(log10)
    CASE(log1p)
    CASE(log2)
    CASE(logb)
    CASE(log)
    CASE(modf)
    CASE(nearbyint)
    CASE(nextafter)
    CASE(pow)
    CASE(remainder)
    CASE(remquo)
    CASE(rint)
    CASE(round)
    CASE(scalbn)
    CASE(sinh)
    CASE(sin)
    CASE(sqrt)
    CASE(tanh)
    CASE(tan)
    CASE(tgamma)
    CASE(trunc)
    CASE(EPSILON)
    CASE(MIN)
    CASE(MIN_POSITIVE)
    CASE(MAX)
    CASE(NAN)
    CASE(INFINITY)
    CASE(NEG_INFINITY)
    CASE(E)
    CASE(FRAC_1_PI)
    CASE(FRAC_1_SQRT_2)
    CASE(FRAC_2_PI)
    CASE(FRAC_2_SQRT_PI)
    CASE(FRAC_PI_2)
    CASE(FRAC_PI_3)
    CASE(FRAC_PI_4)
    CASE(FRAC_PI_6)
    CASE(FRAC_PI_8)
    CASE(LN_2)
    CASE(LN_10)
    CASE(LOG2_10)
    CASE(LOG2_E)
    CASE(LOG10_2)
    CASE(LOG10_E)
    CASE(PI)
    CASE(SQRT_2)
    CASE(TAU)
    reset_fn_buf_state();
}

void calculator_process_char(char c) {
    if (fn_pos == 0) {
        if ((number_read_state != NUMBER_READ_STATE_INITIAL) || (c >= '0' && c <= '9')) {
            parse_number(c);
            return;
        }
        switch (c) {
            case '+':
                run_add();
                return;
            case '-':
                run_sub();
                break;

            case '*':
                run_mul();
                break;

            case '/':
                run_div();
                break;

            case '%':
                run_swap();
                break;
        }
        if (!isalnum(c)) return;
    }

    if (!isalnum(c)) {
        try_run_op();
        return;
    }

    fn_buf[fn_pos++] = c;
    if (fn_pos == 16) {
        try_run_op();
    }
}

#include "calc.h"
#include <math.h>
#include <quantum.h>
#include <stdlib.h>
#include <stdio.h>

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
    int real_length = snprintf(buf, sizeof(buf), "%f", x);
    send_unicode_string(buf);
    tap_code(KC_SPACE);
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

static int pop(double *x) {
    int ent_len;
    if (pop_(x, &ent_len)) {
        while (ent_len--) {
            tap_code(KC_BACKSPACE);
        }
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
        if (!pop(&a)) return;      \
        if (!pop(&b)) return;      \
        push(a op b);              \
    }

def_primop(add, +);
def_primop(sub, -);
def_primop(mul, *);
def_primop(div, /);
/*
#define def_unop(name)             \
    static void run_##name(void) { \
        double a;                  \
        if (!pop(&a)) return;      \
        push((name)(a));           \
    }

#define def_binop(name)            \
    static void run_##name(void) { \
        double a, b;               \
        if (!pop(&a)) return;      \
        if (!pop(&b)) return;      \
        push((name)(a, b));        \
    }

def_unop(cos);
def_unop(sin);
def_unop(tan);
def_unop(acos);
def_unop(asin);
def_unop(atan);
def_binop(atan2);
def_unop(cosh);
def_unop(sinh);
def_unop(tanh);
def_unop(acosh);
def_unop(asinh);
def_unop(atanh);

static void run_frexp(void) {
    double a;
    int    b;
    if (!pop(&a)) return;
    a = frexp(a, &b);
    push(a);
    push(b);
}

def_binop(ldexp);
def_unop(log);
def_unop(log10);

static void modf(void) {
    double a, b;
    if (!pop(&a)) return;
    a = modf(a, &b);
    push(a);
    push(b);
}

def_unop(exp2);
def_unop(expm1);
def_unop(ilogb);
def_unop(log1p);
def_unop(log2);
def_unop(logb);

static void run_scalbn(void) {
    double a, b;
    if (!pop(&a)) return;
    if (!pop(&b)) return;
    push(scalbn(a, (int)b));
}

def_binop(pow);
def_unop(sqrt);
def_unop(cbrt);
def_binop(hypot);
def_unop(erf);
def_unop(erfc);
def_unop(tgamma);
def_unop(lgamma);
def_unop(ceil);
def_unop(floor);
def_binop(fmod);
def_unop(trunc);
def_unop(round);
def_unop(rint);
def_unop(nearbyint);
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

def_binop(copysign);
def_binop(nextafter);
def_binop(fdim);
def_binop(fmax);
def_binop(fmin);
def_monop(fabs);

static void run_fma(void) {
    double a, b, c;
    if (!pop(&a)) return;
    if (!pop(&b)) return;
    if (!pop(&c)) return;
    push(fma(a, b, c));
}*/

void calculator_process_backspace(void) {
    double x;
    if (number_read_state != NUMBER_READ_STATE_INITIAL) {
        finish_number();
    }
    if (!pop(&x)) {
        calculator_disable();
    }
}

void calculator_disable(void) {
    enabled = 0;
}

void calculator_enable(void) {
    enabled = 1;
}

int calculator_is_active(void) {
    return enabled;
}

void calculator_process_char(char c) {
    if ((number_read_state != NUMBER_READ_STATE_INITIAL) || (c >= '0' && c <= '9')) {
        parse_number(c);
        return;
    }
    switch (c) {
        case '+':
            run_add();
            break;
        case '-':
            run_sub();
            break;

        case '*':
            run_mul();
            break;

        case '/':
            run_div();
            break;
    }
}

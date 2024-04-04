UNICODE_ENABLE = yes

SRC += i2c_slave.c i2c_master.c
QUANTUM_SRC += $(QUANTUM_DIR)/split_common/transport.c $(QUANTUM_DIR)/split_common/transactions.c
OPT_DEFS += -DSPLIT_COMMON_TRANSACTIONS
COMMON_VPATH += $(QUANTUM_PATH)/split_common
EXTRAINCDIRS += $(BOARD_PATH)

CFLAGS += -Wl,--defsym=__unhandled_user_irq=_unhandled_exception

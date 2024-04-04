SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = custom
RP2040_INTRINSICS_ENABLED = yes

SRC += i2c_slave.c i2c_master.c
QUANTUM_SRC += $(QUANTUM_DIR)/split_common/transport.c $(QUANTUM_DIR)/split_common/transactions.c
OPT_DEFS += -DSPLIT_COMMON_TRANSACTIONS
COMMON_VPATH += $(QUANTUM_PATH)/split_common
EXTRAINCDIRS += $(BOARD_PATH)

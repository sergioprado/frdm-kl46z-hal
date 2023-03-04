#include "mma8451.h"
#include "fsl_i2c.h"
#include "board.h"

signed short accel_x, accel_y, accel_z;
signed short Aresultx, Aresulty, Aresultz;
char aux1;
int Atestx, Atesty, Atestz;

#define MMA8451_I2C_ADDRESS BOARD_MMA8451_ADDR
#define I2C0_B  BOARD_ACCEL_I2C_BASEADDR

static void BOARD_I2C_Init(I2C_Type *base, uint32_t clkSrc_Hz)
{
    i2c_master_config_t i2cConfig = {0};

    I2C_MasterGetDefaultConfig(&i2cConfig);
    I2C_MasterInit(base, &i2cConfig, clkSrc_Hz);
}

static status_t BOARD_I2C_Send(I2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize)
{
    i2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress = deviceAddress;
    masterXfer.direction = kI2C_Write;
    masterXfer.subaddress = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data = txBuff;
    masterXfer.dataSize = txBuffSize;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(base, &masterXfer);
}

static status_t BOARD_I2C_Receive(I2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize)
{
    i2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress = deviceAddress;
    masterXfer.subaddress = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data = rxBuff;
    masterXfer.dataSize = rxBuffSize;
    masterXfer.direction = kI2C_Read;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(base, &masterXfer);
}

static void BOARD_Accel_I2C_Init(void)
{
    BOARD_I2C_Init(BOARD_ACCEL_I2C_BASEADDR, BOARD_ACCEL_I2C_CLOCK_FREQ);
}

static status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff)
{
    uint8_t data = (uint8_t)txBuff;

    return BOARD_I2C_Send(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, &data, 1);
}

static status_t BOARD_Accel_I2C_Receive(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_I2C_Receive(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, rxBuff, rxBuffSize);
}

void hal_dev_mma8451_init(void)
{
    BOARD_Accel_I2C_Init();
}

// this delay is very important, it may cause w-r operation failure.
static void pause(void)
{
    int n;
    for (n = 0; n < 40; n++)
        __asm__("nop");
}

uint8 hal_dev_mma8451_read_reg(uint8 addr)
{
    uint8_t rxBuff;

    BOARD_Accel_I2C_Receive(MMA8451_I2C_ADDRESS, addr, 1, &rxBuff, 1);
    pause();

    return rxBuff;
}

void hal_dev_mma8451_write_reg(uint8 addr, uint8 data)
{
    BOARD_Accel_I2C_Send(MMA8451_I2C_ADDRESS, addr, 1, (uint32_t) data);
    pause();
}

void accel_init(void)
{
    unsigned char tmp;
    hal_dev_mma8451_init();
    tmp = hal_dev_mma8451_read_reg(0x2a);
    hal_dev_mma8451_write_reg(0x2a, tmp | 0x01);
}

void accel_read(void)
{
    if ((hal_dev_mma8451_read_reg(0x00) & 0xf) != 0) {
        accel_x = hal_dev_mma8451_read_reg(0x01) << 8;
        accel_x |= hal_dev_mma8451_read_reg(0x02);
        accel_x >>= 2;

        accel_y = hal_dev_mma8451_read_reg(0x03) << 8;
        accel_y |= hal_dev_mma8451_read_reg(0x04);
        accel_y >>= 2;

        accel_z = hal_dev_mma8451_read_reg(0x05) << 8;
        accel_z |= hal_dev_mma8451_read_reg(0x06);
        accel_z >>= 2;

        Aresultx = hal_dev_mma8451_read_reg(0x01) << 8;
        Aresultx |= hal_dev_mma8451_read_reg(0x02);
        Aresultx >>= 8;

        Aresulty = hal_dev_mma8451_read_reg(0x03) << 8;
        Aresulty |= hal_dev_mma8451_read_reg(0x04);
        Aresulty >>= 8;

        Aresultz = hal_dev_mma8451_read_reg(0x05) << 8;
        Aresultz |= hal_dev_mma8451_read_reg(0x06);
        Aresultz >>= 8;

    }
}

void accel_read_xyz(int *x, int *y, int *z)
{
    accel_read();
    *x = Aresultx;
    *y = Aresulty;
    *z = Aresultz;
}

int iAcclReadX(void)
{
    if ((hal_dev_mma8451_read_reg(0x00) & 0xf) != 0) {
        accel_x = hal_dev_mma8451_read_reg(0x01) << 8;
        accel_x |= hal_dev_mma8451_read_reg(0x02);
        accel_x >>= 2;

        Aresultx = hal_dev_mma8451_read_reg(0x01) << 8;
        Aresultx |= hal_dev_mma8451_read_reg(0x02);
        Aresultx >>= 8;
    }
    return Aresultx;
}

int iAcclReadY(void)
{
    if ((hal_dev_mma8451_read_reg(0x00) & 0xf) != 0) {
        accel_y = hal_dev_mma8451_read_reg(0x03) << 8;
        accel_y |= hal_dev_mma8451_read_reg(0x04);
        accel_y >>= 2;

        Aresulty = hal_dev_mma8451_read_reg(0x03) << 8;
        Aresulty |= hal_dev_mma8451_read_reg(0x04);
        Aresulty >>= 8;
    }
    return Aresulty;
}

int iAcclReadZ(void)
{
    if ((hal_dev_mma8451_read_reg(0x00) & 0xf) != 0) {
        accel_z = hal_dev_mma8451_read_reg(0x05) << 8;
        accel_z |= hal_dev_mma8451_read_reg(0x06);
        accel_z >>= 2;

        Aresultz = hal_dev_mma8451_read_reg(0x05) << 8;
        Aresultz |= hal_dev_mma8451_read_reg(0x06);
        Aresultz >>= 8;
    }
    return Aresultz;
}

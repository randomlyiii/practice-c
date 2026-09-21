#include <stdint.h>

// 状态枚举
typedef enum
{
    STATE_IDLE,    // 等待帧头
    STATE_LEN,     // 接收长度
    STATE_DATA,    // 接收数据
    STATE_CHECKSUM // 接收校验和
} parser_state_t;

// 解析器结构体
typedef struct
{
    parser_state_t state;
    uint8_t length;
    uint8_t index;
    uint8_t data[255];
    uint8_t checksum;
} frame_parser_t;

// 帧接收完成回调函数，检测到合法完整帧调用
typedef void (*on_frame_received)(const uint8_t *data, uint8_t length);
// 存储回调函数指针
static on_frame_received frame_cb = NULL;

// 初始化解析器
void parser_init(frame_parser_t *p)
{
    p->state = STATE_IDLE;
    p->length = 0;
    p->index = 0;
    p->checksum = 0;
}

// 喂入单字节，核心状态机函数
uint8_t parser_feed(frame_parser_t *p, uint8_t byte)
{
    switch (p->state)
    {
    case STATE_IDLE:
        if (byte == 0xAA) // 收到帧头
        {
            p->checksum = byte; // 校验和包含帧头
            p->state = STATE_LEN;
        }
        break;

    case STATE_LEN:
        p->length = byte;
        p->checksum ^= byte;
        p->index = 0;
        p->state = STATE_DATA;
        break;

    case STATE_DATA:
        p->data[p->index++] = byte;
        p->checksum ^= byte;
        if (p->index >= p->length)
        {
            p->state = STATE_CHECKSUM;
        }
        break;

    case STATE_CHECKSUM:
        if (byte == p->checksum)
        {
            // 校验通过，回调通知上层
            if (frame_cb != NULL)
            {
                frame_cb(p->data, p->length);
            }
        }
        // 无论校验成功失败，切回IDLE等待下一帧
        p->state = STATE_IDLE;
        break;

    default:
        p->state = STATE_IDLE;
        break;
    }
    return p->state;
}

/****************/
// 测试代码 // 仅用于演示解析器功能 // 实际使用时，parser_feed()应在中断或循环中被调用
/****************/
#include <stdio.h>

// 注册回调函数
parser_state_t parser_register_cb(on_frame_received cb)
{
    frame_cb = cb;
    return 0;
}

// 回调函数示例
void frame_callback(const uint8_t *data, uint8_t len)
{
    printf("received frame, len=%d, data: ", len);
    for (int i = 0; i < len; i++)
    {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main(void)
{
    frame_parser_t parser;
    parser_init(&parser);
    parser_register_cb(frame_callback);

    // 构造测试帧：0xAA, 0x02, 0x11,0x22, 校验和 = AA ^ 02 ^11 ^22
    uint8_t test_frame[] = {0xAA, 0x02, 0x11, 0x22, (0xAA ^ 0x02 ^ 0x11 ^ 0x22)};

    for (int i = 0; i < sizeof(test_frame); i++)
    {
        parser_feed(&parser, test_frame[i]);
    }
    // 收到完整帧，len=2, data: 11 22
    return 0;
}

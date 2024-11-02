#include "models/server_status.h"

Models::ServerStatus::ServerStatus(int status) {
    this->status = status;

    data_base_status = DATA_BASE_EXECUTION_STATUS(applyMask(status, DATA_BASE_BITS_COUNT, 0));
    JWT_status = JWT_EXECUTION_STATUS(applyMask(status, JWT_BITS_COUNT, DATA_BASE_BITS_COUNT));
    file_parse_status = FILE_PARSER_EXECUTION_STATUS(applyMask(status, FILE_PARSER_BITS_COUNT, DATA_BASE_BITS_COUNT + JWT_BITS_COUNT));
}

int Models::ServerStatus::applyMask(int number, int bitCount, int bitShift) {
    int mask = 1;

    for (int i = 1; i < bitCount; ++i) {
        mask = (mask << 1) + 1;
    }

    mask <<= bitShift;

    return (number & mask) >> bitShift;
}

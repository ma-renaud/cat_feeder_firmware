#ifndef CONSOLE_CMD_TABLE_H
#define CONSOLE_CMD_TABLE_H

#include <cstdint>
#include "console_type.h"

using namespace console;

namespace master_table {
const commands_table_t** get_master_table();
std::uint32_t& get_master_table_index();
}

namespace base_table {
const commands_table_t* get_base_table();
}

namespace app1_cmd {
const commands_table_t* get_app1_table();
}

namespace app2_cmd {
const commands_table_t* get_app2_table();
}

namespace app3_cmd {
const commands_table_t* get_app3_table();
}

#endif //CONSOLE_CMD_TABLE_H

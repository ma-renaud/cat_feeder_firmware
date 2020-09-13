#include "console_cmd_table.h"
#include "command_parser.h"

using namespace console;

namespace app_cmd {
    // Normally declared & defined elsewhere
    static Cmd_result cmd0(Console_io& io, [[maybe_unused]] const std::pmr::string buffer) { io.print("cmd0 called"); return Cmd_result::success;}
    static Cmd_result cmd1(Console_io& io, [[maybe_unused]] const std::pmr::string buffer) { io.print("cmd1 called"); return Cmd_result::success;}

    constexpr bool option = true;
    static constexpr commands_table_t tbl1_table[] = {
            {"cmd0",  &cmd0, help<option>("cmd0 help")},
            {"cmd1",  &cmd1, help<option>("cmd1 help")},
            {table_end, nullptr, nullptr}
    };

    const commands_table_t* get_app_table()
    {
        return tbl1_table;
    }
}

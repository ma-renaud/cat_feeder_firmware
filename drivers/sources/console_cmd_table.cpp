/*
 * project_commands_template.cpp
 *
 *  Created on: Jan. 8, 2020
 *      Author: christian
 */

#include <cstdint>
#include "console_cmd_table.h"
#include "command_parser.h"

// namespace master_table and base_table would be in the same file. This allow
// the commands in base_table to change the master table index. This file would include the appx_cmd.h

// namespace appx_cmd would be on different .cpp .h files.

using namespace console;

#if 1
namespace master_table {

    static std::uint32_t master_table_index = 0;

    static constexpr size_t nb_table = 4;
    static const commands_table_t*  cli_master_table[nb_table] = { base_table::get_base_table()
                                                                 , app1_cmd::get_app1_table()
                                                                 , app2_cmd::get_app2_table()
                                                                 , app3_cmd::get_app3_table()
                                                                 };

    const commands_table_t** get_master_table()
    {
        return cli_master_table;
    }

    std::uint32_t& get_master_table_index()
    {
        return master_table_index;
    }
}
#endif // Moving master table to Console class

namespace base_table {
    /* Project's commands functions prototypes */
    static Cmd_result cmd0(Console_io& io, const std::pmr::string buffer){ io.print("cmd0 called"); return Cmd_result::success;}
    static Cmd_result cmd1(Console_io& io, const std::pmr::string buffer){ io.print("cmd1 called"); return Cmd_result::success;}
    static Cmd_result cmd2(Console_io& io, const std::pmr::string buffer){ io.print("cmd2 called"); return Cmd_result::success;}
    static Cmd_result cmd3(Console_io& io, const std::pmr::string buffer){ io.print("cmd3 called"); return Cmd_result::success;}
    static Cmd_result cmd4(Console_io& io, const std::pmr::string buffer){ io.print("cmd4 called"); return Cmd_result::success;}
    static Cmd_result tbl1(Console_io& io, const std::pmr::string buffer){ io.print("Enter tbl1"); master_table::master_table_index = 1; return Cmd_result::success;}
    static Cmd_result tbl2(Console_io& io, const std::pmr::string buffer){ io.print("Enter tbl2"); master_table::master_table_index = 2; return Cmd_result::success;}
    static Cmd_result tbl3(Console_io& io, const std::pmr::string buffer){ io.print("Enter tbl3"); master_table::master_table_index = 3; return Cmd_result::success;}

    /* Project's commands table */
    constexpr bool option = false;
    static constexpr commands_table_t base_table[] = {
            {"cmd0",  &cmd0, help<option>("cmd0 help")},
            {"cmd1",  &cmd1, help<option>("cmd1 help")},
            {"cmd2",  &cmd2, help<option>("cmd2 help")},
            {"cmd3",  &cmd3, help<option>("cmd3 help")},
            {"cmd4",  &cmd4, help<option>("cmd4 help")},
            {"tbl1",  &tbl1, help<option>("go to tbl1 help")},
            {"tbl2",  &tbl2, help<option>("go to tbl2 help")},
            {"tbl3",  &tbl3, help<option>("go to tbl3 help")},
            {table_end, nullptr, nullptr}
    };

    const commands_table_t* get_base_table()
    {
        return base_table;
    }
}

namespace app1_cmd {
    // Normally declared & defined elsewhere
    static Cmd_result t1cmd0(Console_io& io, const std::pmr::string buffer) { io.print("t1cmd0 called"); return Cmd_result::success;}
    static Cmd_result t1cmd1(Console_io& io, const std::pmr::string buffer) { io.print("t1cmd1 called"); return Cmd_result::error;}
    static Cmd_result t11(Console_io& io, const std::pmr::string buffer) { io.print("t1 1 called"); return Cmd_result::success;}

    constexpr bool option = true;
    static constexpr commands_table_t tbl1_table[] = {
            {"t1cmd0",  &t1cmd0, help<option>("t1cmd0 help")},
            {"t1cmd1",  &t1cmd1, help<option>("t1cmd1 help")},
            {"1",       &t11, help<option>("1 help")},
            {table_end, nullptr, nullptr}
    };

    const commands_table_t* get_app1_table()
    {
        return tbl1_table;
    }
}

namespace app2_cmd {
    // Normally declared & defined elsewhere
    static Cmd_result t2cmd0(Console_io& io, const std::pmr::string buffer) { io.print("t2cmd0 called"); return Cmd_result::success;}
    static Cmd_result t2cmd1(Console_io& io, const std::pmr::string buffer) { io.print("t2cmd1 called"); return Cmd_result::success;}

    constexpr bool option = true;
    static constexpr commands_table_t tbl2_table[] = {
            {"t2cmd0",  &t2cmd0, help<option>("t2cmd0 help")},
            {"t2cmd1",  &t2cmd1, help<option>("t2cmd1 help")},
            {table_end, nullptr, nullptr}
    };

    const commands_table_t* get_app2_table()
    {
        return tbl2_table;
    }
}

namespace app3_cmd {
    // Normally declared & defined elsewhere
    static Cmd_result t3cmd0(Console_io& io, const std::pmr::string buffer) { io.print("t3cmd0 called"); return Cmd_result::success;}
    static Cmd_result t3cmd1(Console_io& io, const std::pmr::string buffer) { io.print("t3cmd1 called"); return Cmd_result::success;}

    constexpr bool option = true;
    static constexpr commands_table_t tbl3_table[] = {
            {"t3cmd0",  &t3cmd0, help<option>("t3cmd0 help")},
            {"t3cmd1",  &t3cmd1, help<option>("t3cmd1 help")},
            {table_end, nullptr, nullptr}
    };

    const commands_table_t* get_app3_table()
    {
        return tbl3_table;
    }
}

#include <iostream>

#include "protocol.h"

int main (void) {
    JoinMessage join_msg("test_channel");
    LeaveMessage leave_msg("test_channel");
    RegisterMessage register_msg("test_user");
    TextMessage text_msg("Hello, world!", "test_channel");

    uniquePtr<JoinMessage> msg1 = JoinMessage::from_string(join_msg.to_string());

    string str1 = join_msg.to_string();
    string str2 = msg1->to_string();
    if(str1.compare(str2) == 0)
        std::cout << "Join message OK! " << str2 << std::endl;

    uniquePtr<LeaveMessage> msg2 = LeaveMessage::from_string(leave_msg.to_string());
    str1 = leave_msg.to_string();
    str2 = msg2->to_string();
    if(str1.compare(str2) == 0)
        std::cout << "Leave message OK! " << str2 << std::endl;

    uniquePtr<RegisterMessage> msg3 = RegisterMessage::from_string(register_msg.to_string());
    str1 = register_msg.to_string();
    str2 = msg3->to_string();
    if(str1.compare(str2) == 0)
        std::cout << "Register message OK! " << str2 << std::endl;

    uniquePtr<TextMessage> msg4 = TextMessage::from_string(text_msg.to_string());
    str1 = text_msg.to_string();
    str2 = msg4->to_string();
    if(str1.compare(str2) == 0)
        std::cout << "Text message OK! " << str2 << std::endl;
    return 0;
}

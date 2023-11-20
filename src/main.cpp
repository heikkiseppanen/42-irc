#include "ChannelDatabase.hpp"

int main()
{
    ChannelDatabase channels;

    channels.join_channel("Test", "", 1);
    channels.join_channel("Test", "", 1);
    channels.join_channel("Test", "", 2);

    channels.mode("Test", ADD | OPERATOR | USER_LIMIT | PASSWORD, 5, 2, "pass");

    channels.print_all_channels();

    channels.join_channel("Test", "", 3);
    channels.join_channel("Test", "pass", 4);
    channels.join_channel("Test", "pass", 5);

    channels.kick("Test", 5, 2);
    channels.kick("Test", 2, 5);

    channels.change_topic("Test", "Good topic", 1);

    channels.print_all_channels();

    channels.join_channel("Test", "pass", 3);
    channels.join_channel("Test", "pass", 5);
    channels.join_channel("Test", "pass", 6);
    channels.join_channel("Test", "pass", 7);

    channels.print_all_channels();

    channels.change_topic("Test", "Bad topic", 4);

    channels.print_all_channels();
    return 0;
}

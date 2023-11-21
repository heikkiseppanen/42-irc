#include "ChannelDatabase.hpp"

int main()
{
    ChannelDatabase channels;

    channels.join_channel("Test", "", 1);
    channels.join_channel("Test", "", 1);
    channels.join_channel("Test", "", 2);

    Channel& channel = channels.get_channel("Test");
    channels.set_user_limit(channel, ADD, 5);
    channels.set_password(channel, ADD, "pass");
    channels.set_op(channel, 1, 2);

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

#include "ChannelDatabase.hpp"

int main()
{
    ChannelDatabase channels;

    channels.add_channel("Test", 1);
    Channel& channel = channels.get_channel("Test");
    channel.join_channel(1, "");
    channel.join_channel(1, "");
    channel.join_channel(2, "");

    channel.set_user_limit(1, ADD, 5);
    channel.set_password(1, ADD, "pass");
    channel.set_op(1, ADD, 2);

    channels.print_all_channels();

    channel.join_channel(3, "");
    channel.join_channel(4, "pass");
    channel.join_channel(5, "pass");

    channel.kick(2, 5);

    channel.change_topic(1, "Good topic");

    channels.print_all_channels();

    channel.join_channel(3, "pass");
    channel.join_channel(5, "pass");
    channel.join_channel(6, "pass");
    channel.join_channel(7, "pass");

    channels.print_all_channels();

    channel.change_topic(3, "Bad topic");

    channels.print_all_channels();
    return 0;
}

#!/bin/bash

weechat -t -r "/set irc.look.temporary_servers on; /connect 10.1.4.3/$1 -password=$2"
# weechat -t -r "/set irc.look.temporary_servers on; /connect localhost/$1 -password=$2"

#!/bin/bash

weechat -t -r "/set irc.look.temporary_servers on; /connect localhost/$1 -password=$2"
#!/bin/bash
#  Copyright (C) 2005-2010 Julien Jorge, Sebastien Angibaud
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation; either version 2 of the License, or (at your
#  option) any later version.
#
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#  contact: plee-the-bear@gamned.org
#

#-------------------------------------------------------------------------------
# Beginning of the variable declaration

# The name of the level file to run
LEVEL_FILE=

# The number of players
PLAYERS_COUNT=1

# The name of the profile
START_LEVEL=

# The name of the last exit used by the first player
PLAYER_1_EXIT=

# The name of the last exit used by the second player
PLAYER_2_EXIT=

# The name of the profile
PROFILE_NAME="$(whoami)"

# Files extension who are ignored on completion
export FIGNORE=".lvl"

# Test the filepath
FILE_EXISTS="FALSE"

LEVEL_QUESTION=

#-------------------------------------------------------------------------------
# End of the variable declaration

#-------------------------------------------------------------------------------
# This 2 function asks a value to the user and returns his answer.
# \param $1 A description of the value to ask
# \param $2 The default value
ask() {
    if [ "$2" = "" ];then
        echo -e "\E[;32m$1: \E[;0m"
    else
        echo -e "\E[;32m$1 [$2]: \E[;0m"
    fi
} # ask()

# \param $1 The default value
answer(){
    local RESULT="$1"
    local ANSWER=

    read ANSWER
    if [ "$ANSWER" != "" ];then
        RESULT="$ANSWER"
    fi
    echo -e "$RESULT"
} #answer()

#-------------------------------------------------------------------------------
# Run the game.
run_game() {
  ./plee-the-bear $GDB \
    --set-game-var-uint=scenario/players_count="$PLAYERS_COUNT" \
    --set-game-var-string=persistent/scenario/profile_name="$PROFILE_NAME" \
    --set-game-var-string=persistent/"level/$LEVEL_FILE"/player_1/last_exit="$PLAYER_1_EXIT" \
    --set-game-var-string=persistent/"level/$LEVEL_FILE"/player_2/last_exit="$PLAYER_2_EXIT" \
    --start-level="level/$LEVEL_FILE" $ARGS
} # run_game()

#-------------------------------------------------------------------------------
# Run the game with the previous configuration.
auto_run_game() {

  echo -n "Auto starting level $LEVEL_FILE with profile $PROFILE_NAME.";
  echo -n " The first player came from"

  if [ "$PLAYER_1_EXIT" = "" ];then
    echo -n " an anonymous exit."
  else
    echo -n " exit $PLAYER_1_EXIT"
  fi

  if [ "$PLAYERS_COUNT" != 1 ];then
    echo -n " The second player came from"

    if [ "$PLAYER_2_EXIT" = "" ];then
      echo -n " an anonymous exit."
    else
      echo -n " exit $PLAYER_2_EXIT"
    fi
  fi

  echo

  run_game;

} # auto_run_game()

#-------------------------------------------------------------------------------
# Print the available exits
print_exits()
{
    echo
    echo -e "\E[;32mAvailable exit names for player #$1 : \E[;0m"
    grep -A 1 'player_start_position.\(exit_name\|player_index\)' \
        data/level/$LEVEL_FILE \
        | grep -v '^player_start_position.\(exit_name\|player_index\)' \
        | grep -v -- -- \
        | tr '\n' ' ' \
        | sed 's: \([0-9]\): \1\n:g' \
        | awk '{ if ( $2 == "" ) print $1 " "; else print $2 " " $1; }' \
        | grep ^$1 \
        | cut -d' ' -f2
} # print_exits()

AUTO_RUN=
GDB=
ARGS=

for ARG in $@;do
    case "$ARG" in
        --gdb) GDB=gdb;
            ;;
	--again) AUTO_RUN=1;
	    ;;
	--help) echo "$0 [--again] [--help]";
	    echo;
	    echo "This programs fills the arguments required to run Plee the Bear with values asked to the user.";
	    echo;
	    echo "\t--again\tAutomatically run the game with the last configuration.";
	    echo "\t--gdb\tRun the game with gdb.";
	    echo "\t--help\tPrint this message and exit.";
            echo
            ./plee-the-bear --help
	    exit;
	    ;;
        *) ARGS="$ARGS $ARG";
            ;;
    esac
done

# All the parameters will be saved in this file and read again the next time
# this script is read
VARS_FILE=./vars.sh

if [ -f "$VARS_FILE" ];then
  . "$VARS_FILE"

  if [ "$AUTO_RUN" != "" ];then
      auto_run_game;
      exit;
  fi
fi

# Ask for the not determined variables
cd data/
echo -e "\E[;32mAvailable levels : \E[;0m"
find ./ -name *.cl| awk '
{
	print substr($NS,9,expr length $NS)
}
' | column

if [ "$LEVEL_FILE" == "" ];then
    LEVEL_QUESTION="\E[;32mName of the level file : \E[;0m"
else
    LEVEL_QUESTION="\E[;32mName of the level file [$LEVEL_FILE] : \E[;0m"
fi

echo -e $LEVEL_QUESTION
cd -> /dev/null
cd data/level/
while [ "$FILE_EXISTS" == "FALSE" ];do
    read -e ANSWER
    if [ "$ANSWER" == "" ];then
        if [ -e "$LEVEL_FILE" ];then
            FILE_EXISTS="TRUE"
        else
            echo -e "\E[1;31m This file doesn't exist! \E[;0m"
            echo -e $LEVEL_QUESTION
        fi
    elif [ ! -e "$ANSWER" ];then
        echo -e "\E[1;31m This file doesn't exist! \E[;0m"
        echo -e $LEVEL_QUESTION
    else
        LEVEL_FILE=$ANSWER
        FILE_EXISTS="TRUE"
    fi
done
cd -> /dev/null

ask 'Number of players' "$PLAYERS_COUNT"
PLAYERS_COUNT=$(answer "$PLAYERS_COUNT")

print_exits 1

ask 'Last exit for the first player (* to clear)' "$PLAYER_1_EXIT"
PLAYER_1_EXIT=$(answer "$PLAYER_1_EXIT" | sed 's:^\*$::')

if [ "$PLAYERS_COUNT" != "1" ];then
    print_exits 2
    ask 'Last exit for the second player (* to clear)' "$PLAYER_2_EXIT"
    PLAYER_2_EXIT=$(answer "$PLAYER_2_EXIT" | sed 's:^\*$::')
fi

ask 'Name of the profile to use' "$PROFILE_NAME"
PROFILE_NAME=$(answer "$PROFILE_NAME")

# Save the customisation
set +o noclobber
(
  echo LEVEL_FILE=\"$LEVEL_FILE\"
  echo PLAYERS_COUNT=\"$PLAYERS_COUNT\"
  echo PLAYER_1_EXIT=\"$PLAYER_1_EXIT\"
  echo PLAYER_2_EXIT=\"$PLAYER_2_EXIT\"
  echo PROFILE_NAME=\"$PROFILE_NAME\"
) > "$VARS_FILE"

run_game;

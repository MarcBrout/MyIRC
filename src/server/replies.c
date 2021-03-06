/*
** replies.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:40:32 2017 brout_m
** Last update Wed May 31 11:40:50 2017 brout_m
*/
#include "replies.h"

char const	*replies[ERR_END] =
  {
    ":No topic is set",
    "Welcome to the Internet Relay Network",
    ":No such nick/channel",
    ":No such server",
    ":No such channel",
    ":Cannot send to channel",
    ":You have joined too many channels",
    ":There was no such nickname",
    ":Duplicate recipients. No message delivered",
    ":No origin specified",
    ":No recipient given",
    ":No text to send",
    ":No toplevel domain specified",
    ":Wildcard in toplevel domain",
    ":Unknown command",
    ":MOTD File is missing",
    ":No administrative info available",
    ":File error doing",
    ":No nickname given",
    ":Erroneus nickname",
    ":Nickname is already in use",
    ":Nickname collision KILL",
    ":They aren't on that channel",
    ":You're not on that channel",
    ":is already on channel",
    ":User not logged in",
    ":SUMMON has been disabled",
    ":USERS has been disabled",
    ":You have not registered",
    ":Not enough parameters",
    ":You may not reregister",
    ":Your host isn't among the privileged",
    ":Password incorrect",
    ":You are banned from this server",
    ":Channel key already set",
    ":Cannot join channel (+l)",
    ":is unknown mode char to me",
    ":Cannot join channel (+i)",
    ":Cannot join channel (+b)",
    ":Cannot join channel (+k)",
    ":Permission Denied- You're not an IRC operator",
    ":You're not channel operator",
    ":You cant kill a server!",
    ":No O-lines for your host",
    ":Unknown MODE flag",
    ":Cant change mode for other users"
  };

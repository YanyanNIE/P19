#!/usr/bin/python3

import asyncio
from sys import stdin, stdout, stderr, argv
import select


async def envoyer():
    value = input()
    stdout.write(value)

async def recevoir():
    value = ""
    while stdin in select.select([stdin], [], [], 0)[0]:
        line = stdin.readline()
        if line: value += line
    stderr.write(value)

event_loop = asyncio.get_event_loop()

coro_env = envoyer()
coro_rec = recevoir()

event_loop.run_until_complete(coro_env)
event_loop.run_until_complete(coro_rec)



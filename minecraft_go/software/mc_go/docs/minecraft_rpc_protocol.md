# Message Sequences

The message protocol is based off of TCP where there are distinct sections of data transfer:
* Connection
* Data Transmission
* Termination

## Connection

Basic hello exchange to acknowledge that both hosts are connected to one another.

Altera DE2 | Raspberry Pi | Number of Bytes
---        | ---          | ---
\#hi       |              | 3
           | \#hi         | 3

## Receive Coordinates

Request new destination coordinates from the Raspberry Pi Minecraft Server.

Notes           | Altera DE2 | Raspberry Pi | Number of Bytes
---             | ---        | ---          | ---
Request Connect | \#rc       |              | 3
Ack             |            | \#rc         | 3
Send Latitude   |            | ddmm.mmmm    | 9
Echo Latitude   | ddmm.mmmm  |              | 9
Send Longitude  |            | dddmm.mmmm   | 10
Echo Longitude  | dddmm.mmmm |              | 10
Close           | \#rc       |              | 3
Ack             |            | \#rc         | 3

## Journey Complete

Report journey statistics to the Raspberry Pi Minecraft Server

Notes           | Altera DE2 | Raspberry Pi | Number of Bytes
---             | ---        | ---          | ---
Request Connect | \#jc       |              | 3
Ack             |            | \#jc         | 3
Send ElapsedTime| hhh:mm:ss  |              | 9
Echo ElapsedTime|            | hhh:mm:ss    | 9
Send Creep Encs.| xxx        |              | 3
Echo Creep Encs.|            | xxx          | 3
Close           | \#rc       |              | 3
Ack             |            | \#rc         | 3

## Error Handling

The `!` character is reserved for error handling. It can be sent at any time to indicate an error has occurred. Both the Raspberry Pi server and the Altera DE2 client will restore to their state prior to the attempted communication.

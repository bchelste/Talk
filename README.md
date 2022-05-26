# Talk
:envelope:
____
Small data exchange program using UNIX signals.

:large_blue_diamond: The server must be started first. After its launch, it has to print its PID.

:large_blue_diamond: The client takes two parameters:
- The server PID.
- The string to send.
____

- The communication between your client and your server was done only using ***UNIX*** signals.
- it was used only these two signals: ***SIGUSR1*** and ***SIGUSR2***.
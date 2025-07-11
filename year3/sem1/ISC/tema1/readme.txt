Tema 1 ISC

Soundtrack:
~~~sunt conectat la internet non-stop~~~
https://www.youtube.com/watch?v=_rVvjslF6M8

~~~am creierul pentium 4, dar mi s-a ars integratul~~~
https://www.youtube.com/watch?v=VqprMzZXTf4

~~~uite banii, banii, uite cum imi vin... ca eu le stiu codul PIN~~~
https://www.youtube.com/watch?v=H23gnU_ErmE



I. crypto-attack:

Flag:
SpeishFlag{NUMg1PptYkRvfXDKBqRwOpvH5pAvVzIy}

Tools I used:
https://www.dcode.fr/caesar-cipher to break caesar ciphers mindlessly
encrypt0r.py to compute server input and reverse server output to flag

Resources I used:
https://www.youtube.com/watch?app=desktop&v=ZjYzrn8M3w4
https://asecuritysite.com/encryption/c_c
He did the math for me, cheers.

Preliminaries:
- "KLT vahlxg vbiaxkmxqm tmmtvd" is caesar shifted "RSA chosen ciphertext attack",
whatever that means
- "eqqmp ttt.vlrqryb.zlj txqze?s aNt4t9TdUzN" is just a caesar shifted link to
the 1987 hit "Never Gonna Give You Up" by the prolific Rick Astley, I'm sure
this will mean something eventually

The server is fairly communicative, it even outputs errors if you input random
text. This is our first hint:

Please enter your secret message for verification:
xd
Traceback (most recent call last):
  File "/usr/local/bin/crypto-checker.py", line 45, in <module>
    message_obj = json.loads(base64.b64decode(message_enc))
  File "/usr/lib/python3.8/base64.py", line 87, in b64decode
    return binascii.a2b_base64(s)
binascii.Error: Incorrect padding

So the messages we send have to be base64 encoded, meaning that the message we
already have, which we know is valid, is base64 encoded. Decoding it reveals
the public key and the message we need to decrypt:

base64 --decode --wrap=0 message.txt
{"n": 10698506624831129730761861233813354967289673747790853929839597311144848213553868575280809016377185399741519358410139537305031072024501237006407298286239730415856268766311600255605785615278755147439132705117114094663726482021958870743680196193647504692651234705657453594797384135188423215451050474820823974729075535142829182018117064322557490825031066162064784903497615468864117525635321502135976921071845266005383809209011604443882336143676607315772460888329740518338076170906347270380806976014557237907278037281598932362331956866368376256847239506812606963459291038208773464194069084824761989276791338089322989497163,
 "e": 425207,
 "flag": "AQF87zeHLUv5PbMNTvf9XAGcQWTNK6KvkCBACq2E0RtyGtbV6F7aEH9UYkMlCKVIQJqz588Rm7BJGVC3BzCIKsd5Y6HduHrjTq6AGd2s7jD4u41ex3fehb2uaO1PXap+EzTdXk+/8rlAhppexY2N1ICALdIwfFLnhwecu2UjFm5EciDBWqCsJrWpdRb2xR8sFU/lkgfr1jNaFK0zCNkqq9KbUGDIUXalp6Dwo4gfDkzYlsvmMXI9USWMnxixNyZllKN6We9Py7EgPV/IL1nve5yIOmhby+Sss2PoEL5UQ+rWJxVIk2wpL/LcOOO5RDA2XH7o5St9lDdir7Eb/ZUVqCIx"}

Turns out that we have to send jsons that contain the public key and an
encrypted message.

Playing around a bit with the functionalities implemented in encrypt0r.py, we
see that any encrypted message we send to the server will be decrypted, except
the message we already have, shucks.

Using the first hint, turns out you can do some math to turn the message we
already have into a different message, have the server decrypt it and reverse
the mathematical operation to get the flag. This is called a Chosen Ciphertext
Attack.

Here's the math:
ciphertext = message ^ e % n // we need to find the value of message
server_input = ciphertext * r ^ e % n // we send this to the server and have it decrypt it
server_output = server_input^d = (ciphertext * r ^ e)^d = (message^e * r^e)^d = message^ed * r^ed
since message^ed % n = message % n => server_output = message * r

So if we divide the server_output by r, we should get the flag.

All of this can be replicated using the encrypt0r.py script, it will initially
print the server input, and then you can feed it the server output and get the
flag.




II. linux-acl

Flag:
SpeishFlag{iNmjMrlclM1P0tpRKs981kbj1otefP3x}

Solving this included a lot of messing around and finding out that my ideas
were illegal according to Linux (like trying to make a file that has '/'s in
its name). Let's just get straight to the solution though.

In the /usr/local/bin folder there's a some useless scripts, an executable and
a weird implementation of sudo. From one of the scripts, janitor-vacuum.sh, we
can learn how to use this robot-sudo to run executables, as simple as:

robot-sudo /usr/local/bin/vacuum-control

Running this program without robot-sudo doesn't work, running the same program
without giving the full path also doesn't work, running other programs doesn't
work. Weird.
We can investigate robot-sudo using the "strings" utility, doing so reveals
a little bit of info about its implementation, like a path to what seems to be
a configuration file:

/usr/share/vim/talent/r0b0t3rs.conf
which contains:
# syntax: allow <username> <command prefix>
allow gicu /usr/local/.somethingcompiled/th3CEO
allow janitor /usr/local/bin/vacuum-control

So we can make a fairly unwild guess that this file dictates who gets sudo
privileges and on what programs. It also probably means that it compares the
name of the program you give it to the exact path + name that's written in the
configuration file which would explain why "robot-sudo vacuum-control" doesn't
work.

Further investigation using ltrace shows that robot-sudo calls 'strncmp' between
"allow <user> <executable in arg>" and the lines of the configuration file. The
length argument of strncmp seems to be given by the length of the line from the
configuration file, oops. We can exploit this by giving an executable that is
named something like: "full path of program we're trying to run" + "anything
else". This will still match because the first characters will be exactly the
same as one of the lines in the conf file, while the rest of the characters
will not be checked since the strncmp call only checks n characters and n is
the length of the line. For example, we can create a file with the path:

/usr/local/bin/vacuum-control-give-me-a-raise

Executing this file with robot-sudo works, so now we have a file that we can
execute with sudo privileges, but these are only bootleg sudo privileges. We
still can't run commands that require actual privileges like su. So what can we
run? Well, according to the conf file we might be able to run "th3CEO".

Trying this greets us with an "Access denied!" message. Using strings on the
executable shows a random string of characters before a message that would give
us the flag, huh. Giving this as a command line argument to "th3CEO" gives us
our flag, ezpz.




III. binary-exploit:

Flag:
SpeishFlag{fxYZs4l9UEsA9pZnnxnX4fG2Q9fVb58J}

Tools I used:
- ghidra (thank you National Security Agency)
- objdump
- python

I started exploring the binary through objdump, but I couldn't really make out
what arguments it was giving to the first scanf function (what's a 0x804a08d?).
Naturally, I switched to Ghidra to make things easier. Apparently, 0x804a08d
meant "%30[^\n]", I ignored this completely and considered it a fancy way of
saying "%s" which is conveniently unsafe and prone to buffer overflow attacks.

Of course, attacking the program this way doesn't work, at all. "%30[^\n]"
means 30 characters max until new line (or something like that) and the array
was 32 characters long. Back to square one.

Looking into the "loop" function, we see that it reads integers into an
integer array of size 12 until receiving an 'x'. Meaning that we can read as
many integers as we want :^). Ghidra tells us that the array is at an offset of
84 bytes from the return address (and for some bizarre reason the function
doesn't have the usual preamble at the start). Since we're reading integers
that are 4 bytes long, we have to read 84 / 4 = 21 integers to reach the return
address on the stack which we can then replace with the address of the win
function (which we can get from Ghidra/Objdump) represented as an integer, in
our case: 134517302.

Here's a Python command that can generate a good input:
python -c 'import sys; sys.stdout.buffer.write(b"69 " * 21 + b"134517302")'

All you have to do is enter the generated numbers and x to call the win
function. Unfortunately, this is not enough, as the function checks
if its only argument is equal to a secret number, which is calculated at
various points in the program.

The win argument is 4 bytes from the return address (because the EIP is the
last thing we pop from the stack and the argument is at +0x04 from the ebp
according to Ghidra). So adding another number to our input will get us to the
argument, now we just need the correct argument.

The argument we should give is in the variable lucky number, which is updated
at various points in the program. The easiest way I've found to get this value
is to use the fact that the program tells you the value of the lucky number
after every guess if you decide to keep playing. So you can play once, choose
to play again to get the lucky number and append it to your payload, like this:
payload_from_python_command + " another_number" + " lucky_number"

Doing this will reveal the flag.

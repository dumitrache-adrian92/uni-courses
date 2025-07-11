#!/usr/bin/php
<?php
/* Load Config */
require_once(dirname(__FILE__) . '/../config.php');

/** Load Base MVC Objects */
require_once(dirname(__FILE__) . '/..//lib/autoload.php');

$db = new Database(DATABASE_CONFIG);

$messages = array(
	"blue_checkbox" => "Check out our new blue checkboxes for just 8 dollars / month!",
	"spacex_launch" => "Hey, we just launched a new rocket to space!",
);
$message = $messages[$argv[1]];

$count = 0;
$stmt = $db->Query("SELECT `id` FROM `accounts` WHERE `id` > 1", []);
while ($row = $stmt->fetch()) {
	$row["id"];
	$db->Query("INSERT INTO `messages` ".
		"(`sender_id`, `dest_id`, `date`, `read`, `message`) ".
		"VALUES (?, ?, ?, 0, ?)",
		[1, $row["id"], date("Y-m-d H:i:s", time()), $message]);
	$count++;
}

die("DONE!\nAffected: " . $count . ' users.');


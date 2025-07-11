<?php

require_once(dirname(__FILE__).'/_common.php');

class Message extends InsideCommon
{
	protected $message_error = null;

	public function __construct($parent = null) {	
		parent::__construct($parent);
	}

	public function index($params=null)
	{
		$this->_common();
		$userId = $this->authUser['id'];

		// query friends and their messages
		$stmt = $this->db->Query(
			"SELECT a.`id`, a.`username`, a.`fullname`, a.`profile_img`, `f`.valid ".
			"FROM `friends` f INNER JOIN `accounts` a ON f.`friend_id` = a.`id` ".
			"WHERE f.`user_id` = ? ORDER BY a.`id` LIMIT 10", [$userId]);
		$friends = [];
		while ($row = $stmt->fetch()) {
			$msgWhereDest = "(m.`dest_id` = {$userId} AND m.`sender_id` = {$row['id']})";
			$msgWhere = "(m.`sender_id` = {$userId} AND m.`dest_id` = {$row['id']})".
				"    OR $msgWhereDest";
			$stmt2 = $this->db->Query(
				"SELECT ".
				" (SELECT COUNT(*) FROM `messages` AS `m` WHERE ($msgWhere)) AS `count`, ".
				" (SELECT MAX(`date`) FROM `messages` AS `m` WHERE ($msgWhere)) AS `last_date`, ".
				" (SELECT COUNT(*) FROM `messages` AS `m` WHERE ($msgWhereDest) ".
				"    AND `read` = 0) AS `unread` ".
				"");
			$row['stats'] = $stmt2->fetch();
			$friends[] = $row;
		}
		$this->Assign('message_friends', $friends);
		$this->Render("messages");
	}

	public function view($params=null, $unreadOnly=false)
	{
		$this->_common();
		if (empty($params) || empty($params[0])) {
			$this->Assign('errorTitle', "Messages Error");
			$this->Assign('errorDetails', "Invalid parameters!");
			$this->Render("error");
			return;
		}
		if (!empty($_GET["unreadOnly"])) {
			$unreadOnly = true;
		}
		if (!empty($this->message_error)) {
			$this->Assign("error", $this->message_error);
		}
		$userId = $this->authUser['id'];
		$friendId = $params[0];

		$stmt = $this->db->Query("SELECT * FROM `accounts` a ".
			"WHERE a.`id` = ? LIMIT 1", [$friendId]);
		$friendProfile = $stmt->fetch();
		if (empty($friendProfile)) {
			$this->Assign('errorTitle', "Message Error");
			$this->Assign('errorDetails', "User not found!");
			$this->Render("error");
			return;
		}
		$this->Assign('friendProfile', $friendProfile);

		$msgWhereMine = "m.`sender_id` = {$userId} AND m.`dest_id` = {$friendProfile['id']}";
		$msgWhereOther = "m.`dest_id` = {$userId} AND m.`sender_id` = {$friendProfile['id']}";
		$msgWhere = "($msgWhereMine) OR ($msgWhereOther)";
		if ($unreadOnly) {
			$msgWhereOther .= " AND m.`read`=0 ";
			$msgWhere = "($msgWhereOther)";
		}
		$stmt = $this->db->Query(
			"SELECT * FROM (SELECT * FROM `messages` m WHERE $msgWhere ".
			"  ORDER BY `date` DESC LIMIT 20) `t` ORDER BY t.`date` ASC");
		$messages = [];
		$msgIds = [];
		while ($row = $stmt->fetch()) {
			$messages[] = $row;
			if ($row['sender_id'] != $userId && !$row['read'])
				$msgIds[] = $row['id'];
		}
		if (!empty($msgIds)) {
			$this->db->Query("UPDATE `messages` m SET `read`=1 WHERE m.id IN (" . 
				implode(',', $msgIds) . ")");
		}

		$this->Assign('xssSimFriends', XSSIM_IDS);
		$this->Assign('messages', $messages);
		$this->Render('messages_view');
	}

	public function send($params=null)
	{
		$this->_common();
		if (empty($params) || empty($params[0])) {
			$this->Assign('errorTitle', "Messages Error");
			$this->Assign('errorDetails', "Invalid parameters!");
			$this->Render("error");
			return;
		}
		$userId = $this->authUser['id'];
		$friendId = $params[0];
		if (empty($_POST['message'])) {
			$this->message_error = "Empty message!";
			return $this->view($params);
		}
		$stmt = $this->db->Query(
			"SELECT `f`.`friend_id` FROM `friends` f ".
				"WHERE f.`user_id` = ? AND f.`friend_id` = ? AND f.`valid` = 1",
			[$friendId, $userId]);
		if (!($stmt->fetch())) {
			$this->message_error = "Unable to send message: friendship unapproved!";
			return $this->view($params);
		}
		$message = $_POST['message'];
		$this->db->Query("INSERT INTO `messages` ".
			"(`sender_id`, `dest_id`, `date`, `read`, `message`) ".
			"VALUES (?, ?, ?, 0, ?)",
			[$userId, $friendId, date("Y-m-d H:i:s", time()), $message]);

		$this->Redirect('/inside/message/view/' . rawurlencode($friendId));
	}

	public function nuke($params=null)
	{
		$this->_common();
		if (empty($params) || empty($params[0])) {
			$this->Assign('errorTitle', "Messages Error");
			$this->Assign('errorDetails', "Invalid parameters!");
			$this->Render("error");
			return;
		}
		$userId = $this->authUser['id'];
		$friendId = $params[0];
		$msgWhere = "(m.`sender_id` = {$userId} AND m.`dest_id` = {$friendId}) OR ".
			"    (m.`dest_id` = {$userId} AND m.`sender_id` = {$friendId})";
		// intentional injection (why not?)
		$this->db->Query("DELETE FROM `messages` m WHERE $msgWhere");

		$this->Redirect('/inside/message');
	}

}


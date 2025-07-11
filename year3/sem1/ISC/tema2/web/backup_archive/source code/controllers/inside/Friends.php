<?php

require_once(dirname(__FILE__).'/_common.php');

class Friends extends InsideCommon
{
	public function __construct($parent = null) {	
		parent::__construct($parent);
	}

	public function add($param=null)
	{
		if (empty($_GET['id'])) {
			echo '{ "error": "invalid friend ID" }';
			return;
		}
		try {
			$uid = $this->authUser['id'];
			$friendId = $_GET['id'];
			$stmt = $this->db->Query("SELECT * FROM `friends` ".
				"WHERE `user_id` = ? AND `friend_id` = ?",
				[$uid, $friendId]);
			$friend = $stmt->fetch();
			if ($friend) {
				echo '{ "error": "already added to friends!" }';
			} else {
				$this->db->Query("INSERT INTO `friends` (`user_id`, `friend_id`, `valid`) ".
					"VALUES (?, ?, 1), (?, ?, 0)",
					[$uid, $friendId, $friendId, $uid]);
			}
			echo '{ "success": true }';
			return;
		} catch (\Exception $e) {
			echo json_encode(["error" => $e->getMessage()]);
			return;
		}
	}

	public function accept() {
		if (empty($_GET['id'])) {
			echo '{ "error": "invalid friend ID" }';
			return;
		}
		$uid = $this->authUser['id'];
		$friendId = $_GET['id'];
		try {
			$this->db->Query("UPDATE `friends` SET `valid` = 1 ".
				"WHERE (`user_id` = ? AND `friend_id` = ?)",
				[$uid, $friendId]);
			echo json_encode(["success" => true]);
		} catch (\Exception $e) {
			echo json_encode(["error" => $e->getMessage()]);
			return;
		}
	}

}


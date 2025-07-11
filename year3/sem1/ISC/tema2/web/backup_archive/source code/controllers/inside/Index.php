<?php

require_once(dirname(__FILE__).'/_common.php');
require_once(dirname(__FILE__).'/Profile.php');

class Index extends InsideCommon
{
	public function __construct($parent = null) {	
		parent::__construct($parent);
	}

	public function index()
	{
		$this->_common();
		$userId = $this->authUser['id'];
		$stmt = $this->db->Query(
			"SELECT p.*, a.`username`, a.`fullname`, a.`profile_img` ".
			"FROM `posts` p LEFT JOIN `accounts` a ON p.`user_id` = a.`id` ".
			"WHERE p.`visibility` = 0 OR ".
			"  EXISTS (SELECT f.user_id FROM `friends` f WHERE ".
			"    f.user_id = p.user_id AND f.friend_id = ? AND f.valid = 1) ".
			"ORDER BY `date` DESC LIMIT 20", [$userId]);
		$posts = [];
		while ($row = $stmt->fetch()) {
			/* replace for Task 2 (XSS) - avoid storing multiple flags inside database! */
			if ($row['username'] == 'theboss' && $row['visibility']) {
				$row['post'] = str_replace('${BOSS_FLAG_NOT_IN_DATABASE}', BOSS_FLAG, $row['post']);
			}
			$posts[] = $row;
		}
		$this->Assign('posts', $posts);

		$this->Assign('newPost_err', '');
		if (!empty($_SESSION['newPost_err'])) {
			$this->Assign('newPost_err', $_SESSION['newPost_err']);
			unset($_SESSION['newPost_err']);
		}

		$this->Render();
	}

	function Dispatch($components, $forceAction = NULL)
	{
		if (!empty($components) && $components[0] == 'p') {
			$profileControl = new Profile($this);
			$profileControl->Dispatch(array_slice($components, 1), 'index');
		} else {
			parent::Dispatch($components, $forceAction);
		}
	}

}


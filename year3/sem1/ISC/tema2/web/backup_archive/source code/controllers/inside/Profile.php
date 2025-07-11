<?php

require_once(dirname(__FILE__).'/_common.php');

class Profile extends InsideCommon
{
	public function __construct($parent = null) {	
		parent::__construct($parent);
	}

	public function index($params=null)
	{
		$this->_common();
		if (empty($params)) {
			$this->Render("profile_404");
			return;
		}
		// make the profile accessible by either ID or username
		$u = $params[0];
		$cond = "a.`username` LIKE '{$u}'";
		if (preg_match('/^[0-9]+$/', $u)) {
			$cond = "a.`id` = {$u}";
		}
		$stmt = $this->db->Query(
			"SELECT *, EXISTS (SELECT f.user_id FROM `friends` f WHERE ".
			"   f.user_id = a.id AND f.friend_id = ?) AS `friend_added` ".
			"FROM `accounts` a ".
			"WHERE {$cond} LIMIT 1",
			[$this->authUser['id']]);
		$profile = $stmt->fetch();
		if (empty($profile)) {
			$this->Render("profile_404");
			return;
		}
		$this->Assign('profile', $profile);

		$stmt = $this->db->Query(
			"SELECT p.*, a.`username`, a.`fullname`, a.`profile_img`, ".
			"  EXISTS (SELECT f.user_id FROM `friends` f WHERE ".
			"    f.user_id = p.user_id AND f.friend_id = ? AND f.valid = 1) AS `friend_post` ".
			"FROM `posts` p LEFT JOIN `accounts` a ON p.`user_id` = a.`id` ".
			"WHERE p.`user_id` = ? ".
			"ORDER BY `date` DESC LIMIT 10",
			[$this->authUser['id'], $profile['id']]);
		$posts = [];
		while ($row = $stmt->fetch()) {
			/* replace for Task 2 (XSS) - avoid storing multiple flags inside database! */
			if ($row['username'] == 'theboss' && $row['visibility']) {
				$row['post'] = str_replace('${BOSS_FLAG_NOT_IN_DATABASE}', BOSS_FLAG, $row['post']);
			}
			$posts[] = $row;
		}
		$this->Assign('posts', $posts);

		$this->Render();
	}

}


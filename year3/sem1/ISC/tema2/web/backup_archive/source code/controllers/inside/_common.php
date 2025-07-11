<?php

if (file_exists(__DIR__ . "/_xssim.php"))
	require_once(__DIR__ . "/_xssim.php");

/**
 * Common functions used by all controllers.
 */
class InsideCommon extends Controller
{
	protected $authUser = null;

	public function __construct($parent = null) {	
		$this->usesDatabase = true;
		$this->templatePath = '/inside';
		$this->controllerPath = '/inside';
		parent::__construct($parent);

		if (empty($parent) && class_exists("_xssim")) {
			/* override authenticated object using _xSSim */
			_xssim::checkXSSMockAuth($this);
		}
		else if ($parent && !empty($parent->authUser)) {
			$this->authUser = $parent->authUser;
		}
		if (empty($this->authUser) && !empty($_SESSION['auth'])) {
			$this->authUser = $_SESSION['auth'];
		}
	}

	protected function _common()
	{
		if (empty($this->authUser)) {
			$this->Redirect('/?err=403');
		}
		$userId = $this->authUser['id'];
		$this->Assign('authUser', $this->authUser);
		$this->Assign('userId', $userId);

		$stmt = $this->db->Query(
			"SELECT a.`id`, a.`username`, a.`fullname`, a.`profile_img`, `f`.`valid`, ".
				"(SELECT `valid` FROM `friends` o WHERE o.`friend_id`=f.`user_id` ".
				"AND o.`user_id`=f.`friend_id`) AS `accepted`" .
			"FROM `friends` f INNER JOIN `accounts` a ON f.`friend_id` = a.`id` ".
			"WHERE f.`user_id` = ? ORDER BY a.`id` LIMIT 10", [$userId]);
		$friends = [];
		while ($row = $stmt->fetch()) {
			$friends[] = $row;
		}
		$this->Assign('friends', $friends);

		$userId = $this->authUser['id'];
		$stmt = $this->db->Query(
			"SELECT a.`username`, a.`fullname`, a.`profile_img` ".
			"FROM `accounts` a ".
			"WHERE a.`id` <> ? AND NOT EXISTS (".
			"  SELECT 1 FROM `friends` `f` WHERE (f.friend_id = a.id AND f.user_id = ?) ".
			"    OR (f.friend_id = a.id AND f.friend_id = ?) ) ".
			"ORDER BY RAND() LIMIT 5", [$userId, $userId, $userId]);
		$youmayknow = [];
		while ($row = $stmt->fetch()) {
			$youmayknow[] = $row;
		}
		$this->Assign('youmayknow', $youmayknow);
	}
	
}


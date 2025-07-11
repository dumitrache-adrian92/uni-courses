<?php
require_once(dirname(__FILE__).'/_common.php');

class Post extends InsideCommon
{
	public function __construct($parent = null) {	
		parent::__construct($parent);
	}

	public function create()
	{
		$_SESSION['newPost_err'] = null;
		try {
			if (empty($_POST['text'])) {
				throw new RuntimeException('Empty post text!');
			}
			$uploadName = '';
			$noFile = true;
			$postBody = htmlentities($_POST['text']);
			if (!empty($_FILES)) {
				$noFile = false;
				switch ($_FILES['image']['error']) {
					case UPLOAD_ERR_OK:
						break;
					case UPLOAD_ERR_NO_FILE:
						$noFile=true; break;
					case UPLOAD_ERR_INI_SIZE:
					case UPLOAD_ERR_FORM_SIZE:
						throw new RuntimeException('Exceeded filesize limit.');
					default:
						throw new RuntimeException('File upload error (invalid request).');
				}
			}
			if (!$noFile) {
				// store the file on the server
				// Note: do not trust MIME from the user agent, compute our own
				// instead; this should do the trick to avoid malicious
				// uploading of PHP code, right?
				$finfo = new finfo(FILEINFO_MIME_TYPE);
				$mime = $finfo->file($_FILES['image']['tmp_name']);
				if (array_search($mime, ['image/jpeg', 'image/png',
						'image/gif']) === false) {
					throw new RuntimeException("Invalid file format: $mime not allowed!");
				}
				$uploadDest = PARENT_DIR . '/userupload';
				$date = time();
				$uploadName = "posts/" . preg_replace('/(\.[a-zA-Z])$/', $date,
					$_FILES['image']['name']);
				if (!move_uploaded_file($_FILES['image']['tmp_name'],
						"$uploadDest/$uploadName")) {
						throw new RuntimeException("Failed to move uploaded file to ".
							"'$uploadDest/$uploadName'!");
				}
			}
			$this->db->Query("INSERT INTO `posts` ".
				"(`date`, `user_id`, `visibility`, `post`, `image`) ".
				"VALUES (?, ?, 0, ?, ?)",
				[date("Y-m-d H:i:s", time()), $this->authUser['id'],
				 $postBody, $uploadName]);

			$this->Redirect('/inside');return;

		}  catch (RuntimeException $e) {
			$_SESSION['newPost_err'] = $e->getMessage();
			$this->Redirect('/inside');return;
		}
	}
}


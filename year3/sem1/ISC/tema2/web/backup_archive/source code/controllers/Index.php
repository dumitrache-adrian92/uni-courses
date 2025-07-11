<?php

class Index extends Controller
{
	public function __construct($parent = null) {	
		parent::__construct($parent);
	}
	
	public function index()
	{
		if (!empty($_SESSION['auth'])) {
			$this->Redirect('/inside');
		}
		if (!empty($_GET["err"])) {
			$errMsgs = array(
				"403" => "Access denied!",
				"404" => "Page not found!",
				"login" => "Felin failed!",
				"default" => "There was an error processing your request!"
			);
			$this->assign("error", isset($errMsgs[$_GET['err']])?
				$errMsgs[$_GET['err']] : $errMsgs["default"]);
		}
		$this->Render();
	}
	
}



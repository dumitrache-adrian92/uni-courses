<?php

class ErrorController extends Controller
{
	public function __construct($parent = null) {	
		parent::__construct($parent);
	}

	public function index($params)
	{
		$title = "Error";
		$details = "An unknown error has occurred!";
		if (!empty($params)) {
			$title = $params[0];
			if (!empty($params[1]))
				$details = $params[1];
		}
		$this->Assign("errorTitle", $title);
		$this->Assign("errorDetails", $details);
		$this->Render("error");
	}

	public function error404($params)
	{
		$title = "404 Error (Not Found)";
		$details = "<h3>File not found!</h3>";
		if (!empty($params)) {
			$details = $params[0];
		}
		$this->Assign("errorTitle", $title);
		$this->Assign("errorDetails", $details);
		http_response_code(404);
		$this->Render("error");
	}
	
}

/* Error is reserved by PHP, so we rename our controller class... */
$controller = "ErrorController";


<?php


class Index extends Controller
{
	protected $authUser = null;

	public function __construct($parent = null) {	
		$this->usesDatabase = true;
		$this->templatePath = '/admin';
		$this->controllerPath = '/admin';
		parent::__construct($parent);

		$this->authUser = null;
		if (!empty($_SESSION['auth'])) {
			$this->authUser = $_SESSION['auth'];
		}
		if (!empty($this->authUser)) {
			$userId = $this->authUser['id'];
			$this->Assign('authUser', $this->authUser);
			$this->Assign('userId', $userId);
		}
	}

	public function index() {
		if (empty($this->authUser) || $this->authUser['privilege'] < 90) {
			$this->Redirect('/?err=403');
		}
		$this->Render();
	}

	public function runScript() {
		if (empty($this->authUser) || $this->authUser['privilege'] < 90) {
			$this->Redirect('/?err=403');
		}
		if (empty($_POST["name"])) {
			$this->Assign('errorTitle', "Script Error");
			$this->Assign('errorDetails', "Invalid script parameters!");
			$this->Render(VIEWS . "inside/error.phtml");
		}
		$cmd = explode(" ", $_POST["name"]);
		if (sizeof($cmd) > 2) {
			$this->Assign('errorTitle', "Script Error");
			$this->Assign('errorDetails', "Too many arguments!");
			$this->Render(VIEWS . "inside/error.phtml");
		}
		$scriptName = PARENT_DIR . '/bin/' . $cmd[0];
		if (!file_exists($scriptName)) {
			$this->Assign('errorTitle', "Script Error");
			$this->Assign('errorDetails', "Script not found: '$scriptName'");
			$this->Render(VIEWS . "inside/error.phtml");
			return;
		}
		// hahah :P
		if (preg_match("/\\brm\\b/", $scriptName)) {
			$this->Assign('errorTitle', "Script Error");
			$this->Assign('errorDetails', "Hey, no rm'ing, please!");
			$this->Render(VIEWS . "inside/error.phtml");
			return;
		}
		$strCmd = '';
		$first = true;
		foreach ($cmd as $arg) {
			if ($first) {
				$arg = $scriptName;
				$first = false;
			}
			if (!empty($strCmd)) { $strCmd .= ' '; }
			$strCmd .= escapeshellarg($arg);
		}
		$output = null;
		$retVal = null;
		exec("timeout 10s " . $strCmd, $output, $retVal);
		$this->Assign('scriptRet', $retVal);
		$this->Assign('scriptOut', implode("\n", $output));
		$this->Render("index");
	}
}

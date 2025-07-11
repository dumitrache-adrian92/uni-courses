<?php

class Auth extends Controller
{
	public function __construct($parent = null) {	
		$this->usesDatabase = true;
		parent::__construct($parent);
	}
	
	public function login()
	{
		if (!empty($_POST)) {
			if (empty($_POST["catname"]) || empty($_POST["password"]) || empty($_POST["agreement"])) {
				error_log("Invalid POST parameters: " . var_export($_POST, true));
				$this->Redirect("/?err=login");return;
			}
			$stmt = $this->db->Query("SELECT * FROM `accounts` WHERE username = ? AND password = SHA(?)",
				array($_POST["catname"], $_POST["password"]));
			$account = $stmt->fetch();
			if (!$account) {
				error_log("Invalid credentials: " . var_export($_POST, true));
				$this->Redirect("/?err=login");return;
			}
			$_SESSION["auth"] = $account;
		}
		$this->Redirect("/");
	}

	public function fake_register()
	{
		$this->Render('register_fake');
	}
	
	public function register_real_one()
	{
		if (!empty($_POST)) {
			if (empty($_POST["fullname"]) || empty($_POST["catname"]) ||
					empty($_POST["password"]) || empty($_POST["agreement"])) {
				$this->Assign("error", "All fields are required!");
				$this->Render("register");return;
			}
			if ($_POST["password"] != $_POST["confirm_password"]) {
				$this->Assign("error", "Passwords do not match!");
				$this->Render("register");return;
			}
			try {
				$stmt = $this->db->Query("SELECT * FROM `accounts` WHERE username = ?",
					array($_POST["catname"]));
				$account = $stmt->fetch();
				if ($account) {
					$this->Assign("error", "That account already exists!");
					$this->Render("register");return;
				}
				$this->db->Query("INSERT INTO `accounts` (`privilege`, `fullname`, `username`, `password`) ".
					"VALUES (0, ?, ?, SHA(?))",
					array($_POST["fullname"], $_POST["catname"], $_POST["password"]));
				$this->Assign("success", "Account was successfully created! " .
					"<a href=\"/\">Try to login now</a>.");
			} catch (\PDOException $e) {
				error_log("PDO Error while inserting into `account`: " . $e->getMessage());
				$this->Assign("error", $e->getMessage());
			}
		}
		$this->Render('register');
	}

	public function logout()
	{
		$_SESSION['auth'] = null;
		$this->Redirect("/");
	}
}


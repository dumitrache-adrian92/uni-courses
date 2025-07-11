<?php

class Database
{
	protected $config = null;
	protected $connected = false;

	public $link = null;

	/**
	 * Database constructor.
	 */
	public function __construct($config)
	{
		$this->config = $config;
	}

	public function Connect()
	{
		if ($this->link) return;

		$host = $this->config["host"];
		$db   = $this->config["database"];
		$user = $this->config["username"];
		$pass = $this->config["password"];
		$charset = 'utf8mb4';
		$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
		$options = [
			PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
			PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
			PDO::ATTR_EMULATE_PREPARES   => false,
		];
		try {
			$this->link = new PDO($dsn, $user, $pass, $options);
		} catch (\PDOException $e) {
			// rethrow the exception to avoid outputting the traceback (contains
			// the valut of the $pass variable!)
			throw new \PDOException($e->getMessage(), (int)$e->getCode());
		}
	}

	public function Query($query, $inputValues=null)
	{
		$this->Connect();
		$stmt = $this->link->prepare($query);
		$stmt->execute($inputValues);
		return $stmt;
	}

}



<?php

class Controller
{
	protected $controllerPath = '';
	protected $templatePath = '';
	protected $usesSessions = true;
	protected $usesDatabase = false;
	protected $db = null;

	/**
	 * Base constructor.
	 */
	public function __construct($parent = null)
	{
		$this->view	= new View(VIEWS . '/' . $this->templatePath);
		if (!empty($parent)) {
			// we were called by another controller
			// get the already initialized database & view variables
			$this->db = $parent->db;
			$this->view->import_data($parent->view);

		} else {
			// use sessions?
			if ($this->usesSessions) {
				session_start();
			}
			
			/** Load Database */
			if ($this->usesDatabase)
				$this->db = new Database(DATABASE_CONFIG);
		}
	}

	/**
	 * Primary action dispatch method.
	 *
	 * Default implementation searches for a method named after the first URI
	 * component and falls back to 'index'.
	 * If neither is found, shows an error page.
	 *
	 * @param {bool} $forceAction If true, it will dispatch the parameters to
	 * that specific action.
	 */
	public function Dispatch($components, $forceAction=null)
	{
		/* default action: index */
		$action = DEFAULT_CONTROLLER_METHOD;
		if ($forceAction) {
			$action = $forceAction;
		} else if (!empty($components)) {
			/* action is the first path segment, 
			 * the rest are arguments received by it */
			$action = $components[0];
			$components = array_slice($components, 1);
		}
		$this->Assign("currentControllerName", get_class($this));
		$this->Assign("currentController", $this->controllerPath . '/' . strtolower(get_class($this)));
		$this->Assign("currentAction", $action);
		try {
			$method = new \ReflectionMethod($this, $action);
			if (!empty($components) && $method->getNumberOfParameters()) {
				$this->$action($components);
			} else {
				$this->$action();			
			}

		} catch (\ReflectionException $exception) {
			require_once(CONTROLLERS . "/Error.php");
			$errorCntrl = new ErrorController($this);
			return $errorCntrl->error404([$exception->getMessage()]);
		}
	}

	/**
	 * Asssign a value to view.
	 *
	 * @param str $key Variable name
	 * @param str $val Value of the Assignment
	 */
	public function Assign($key, $val)
	{
		$this->view->data[$key] = $val;
	}

	/**
	 * Renders the page.
	 *
	 * @param str $view Use for a custom view to render
	 */
	public function Render($view = NULL)
	{
		if (empty($view))
			$view = strtolower(get_class($this));
		echo $this->view->render($view);
	}

	/**
	 * Redirects to a target URL.
	 *
	 * @param str $url The page to redirect to.
	 */
	public function Redirect($url)
	{
		header("Location: $url");
		die();
	}

	/**
	 * Routes a request to its appropriate controller.
	 */
	public static function RouteRequest($reqComponents)
	{
		/* first, find the controller's sub-directory */
		$curPath = CONTROLLERS;
		while (!empty($reqComponents)) {
			$component = reset($reqComponents);
			if (is_dir("$curPath/$component")) {
				$curPath .= "/$component";
				array_shift($reqComponents);
			} else break;
		}
		/* try to search current path for controller classes */
		$try_files = [
			["$curPath/" . DEFAULT_CONTROLLER . ".php", DEFAULT_CONTROLLER, 0]
		];
		if (!empty($reqComponents)) {
			$component = reset($reqComponents);
			$className = ucfirst(strtolower($component));
			array_unshift($try_files, ["$curPath/$className.php", $className, 1]);
			array_unshift($try_files, ["$curPath/$className", $className, 1]);
		}
		$params = $reqComponents;
		$controller = null;
		$controllerFile = null;
		foreach ($try_files as $desc) {
			if (file_exists($desc[0])) {
				$controller = $desc[1];
				$controllerFile = $desc[0];
				$params = array_slice($reqComponents, $desc[2]);
				break;
			}
		}
		return [$controller, $controllerFile, $params, $try_files];
	}

}


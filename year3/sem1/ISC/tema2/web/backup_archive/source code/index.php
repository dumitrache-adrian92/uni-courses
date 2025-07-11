<?php
/* Load config */
require_once(dirname(__FILE__) . '/config.php');
/* Load class autoloader */
require_once(dirname(__FILE__) . '/lib/autoload.php');

// parse the 'p' path received from nginx
$url = empty($_GET['p']) ? "" : $_GET['p'];
// remove leading slash
$url = (!empty($url) && $url[0] == '/') ? substr($url, 1) : $url;
$urlComponents = explode('/', $url);

/** Find the Controller and Instantiate it */
[$controller, $controllerFile, $params, $try_files] = Controller::RouteRequest($urlComponents);

if (empty($controller) || !file_exists($controllerFile)) {
	$controller = "Error";
	$controllerFile = CONTROLLERS . "/$controller.php";
	$errorDetail = "<h3>The controller was not found!</h3>\n".
		"The following files were tried: \n";
	foreach ($try_files as $fileDesc) {
		$errorDetail .= "$fileDesc[0]\n";
	}
	$errorDetail .= "\nGET parameters: ".var_export($_GET, true);
	$params = ["error404", $errorDetail];
}

require_once($controllerFile);
$object = new $controller();
$object->Dispatch($params);


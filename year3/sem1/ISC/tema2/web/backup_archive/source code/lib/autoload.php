<?php

DEFINE ('PARENT_DIR', dirname(dirname(__FILE__)));

DEFINE ('CONTROLLERS',	PARENT_DIR . '/controllers');
DEFINE ('MODELS',		PARENT_DIR . '/models');
DEFINE ('VIEWS',		PARENT_DIR . '/views');
DEFINE ('LIBRARY',		PARENT_DIR . '/lib');

DEFINE('DEFAULT_CONTROLLER',	'Index');

/**
*	The default method to run if a method is not defined
*	@example This checks controller->index();
*/
DEFINE('DEFAULT_CONTROLLER_METHOD', 'index');

DEFINE('AUTOLOAD_Database',	true);

/**
 * Autoload Objects, Class names must match File names
 */
spl_autoload_register(function ($class) {
	/** Class categories / folders. */
	$sections = array(
		LIBRARY,
	);
	/** Iterate: Require each Object */
	foreach ($sections as $dir) {
		if (file_exists("$dir/$class.php")) {
			require_once("$dir/$class.php");
			return;
		}
	}
});


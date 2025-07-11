<?php

class View
{
	/**
	 * The directory where template files are found.
	 */
	public $templateDir = "";

	/**
	 * Set data from controller: $view->data['variable'] = 'value';
	 * @var array
	 */
	public $data = [];

	/**
	 * Base constructor.
	 * @param $templateDir The directory where template files are found.
	 */
	public function __construct($templateDir) {
		$this->templateDir = $templateDir;
	}

	/**
	 * @var sting Path to template file.
	 */ 
	function render($template)
	{
		if ($template[0] != DIRECTORY_SEPARATOR) {
			// relative path
			$template = $this->templateDir . DIRECTORY_SEPARATOR . $template . ".phtml";
		}
		if (!is_file($template)) {
			throw new \RuntimeException('Template not found: ' . $template);
		}

		// define a closure with a scope for the variable extraction
		$result = function($file, array $data = array()) {
			ob_start();
			extract($data, EXTR_SKIP);
			try {
				include($file);
			} catch (\Exception $e) {
				ob_end_clean();
				throw $e;
			}
			return ob_get_clean();
		};

		// call the closure
		return $result($template, $this->data);
	}

	/**
	 * Imports the data from another view.
	 */
	function import_data($view, $replace=false)
	{
		if ($replace) {
			$this->data = array_merge($this->data, $view->data);
		} else {
			$this->data = array_merge($view->data, $this->data);
		}
	}
}


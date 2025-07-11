/**
 * Task development support functions.
 * If you are a student and see this, I have failed epically :(( 
 */

function devLogin(username, password) {
  var $form = $("form");
  $form.find("input[name=username]").val(username);
  $form.find("input[name=password]").val(password);
  $form.find("input[name=agreement]").prop("checked", true);
  $form.submit();
}


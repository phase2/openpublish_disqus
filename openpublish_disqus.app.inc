<?php
/*
 * implements hook_apps_app_info
 */
function openpublish_disqus_apps_app_info() {
  return array(
    'configure form' => 'openpublish_disqus_configure',
  );
}
/*
 * implements the configure form for the openpublish_disqus app
 */
function openpublish_disqus_configure($form, $form_state) {
  $domain = variable_get("disqus_domain", false);
  module_load_include("inc", "disqus", "disqus.admin");
  $disqus_form = disqus_admin_settings();
  if ($domain) {
    $form = $disqus_form;
    $form['settings']['#default_tab'] = 'visibility';
  }
  else {
    $form['getting_started'] = array(
      '#type' => 'fieldset',
      '#title' => 'Getting Started with Disqus Commenting',
    );
    $form['getting_started']['info'] = array(
      '#markup' => t('To get started using Disqus for commenting you need to tell drupal the disqus domain short name. If you do not have a disqus domain short name you can get one on the <a href="http://disqus.com/admin/register/">Disqus Registration site</a>.'),
    );
    $form['disqus_domain'] = $disqus_form['disqus_domain'];
    $form['getting_started_warning'] = array(
      '#type' => 'fieldset',
      '#title' => 'Drupal Comments Warning',
      '#attributes' => array("class"=>array("warning")),
    );
    $form['getting_started_warning']['warning'] = array(
      '#markup' => t('Standard Drupal Commenting will be disabled, which mean that those comments will no longer appear or be accessable. (One will beable to recover them by enabled the comments module).'),
    );
    $form['submit'] = array('#type' => 'submit', '#value' => t('Enable Disqus Commenting'));
  }
  //debug($form);
  return $form;
}
function openpublish_disqus_configure_submit($form, $form_state) {
  openpublish_disqus_enable($form_state['values']['disqus_domain']);
}

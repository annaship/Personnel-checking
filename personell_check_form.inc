<?php

//require_once('personell_check_form_submit.inc');

function personell_check_form($form_state) {
  $form = array();
  unset($last_settings);
  $new_person_nid  = variable_get('new_person_nid', '');
//  $new_person_node = _get_new_person_node($new_person_nid);
  $old_person_nids = variable_get('old_person_nids', '');
  $new_last_name   = $new_person_node['last_name'];
//  $old_person_nids = ($new_last_name);

//  $nodes = $new_person_node;
//  $nodes += _personell_check_items($old_person_nids);

  $new_a = array();
  $new_a[] = node_load($new_person_nid);
  $old_a = _personell_check_items($old_person_nids);

  $nodes = array_merge($new_a, $old_a);

//  $nodes = _personell_check_items($old_person_nids);

  $form['container'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#theme' => 'personell_check_form_table',
  );

  foreach($nodes as $node) {
    $form['container']['node_' . $node->nid] = array(
      '#type' => 'checkbox',
      '#title' => NULL,
      '#size' => 4,
      '#default_value' => 0,
    );
  }

//  $form['new_person'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('New personnel data'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//
//  $form['new_person']['first_name'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('First name'),
//    // '#required'  => TRUE,
//    '#size'  => 30,
//    '#maxlength' => 30,
//    '#default_value' => $new_person_node['first_name'],
//    // '#description' => t('Site name acronym'),
//  );
//
//    $form['new_person']['last_name'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('Last name'),
//    // '#required'  => TRUE,
//    '#size'  => 30,
//    '#maxlength' => 30,
//    '#default_value' => $new_person_node['last_name'],
//    // '#description' => t('Site name acronym'),
//  );
//
//    $form['new_person']['email'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('Email'),
//    // '#required'  => TRUE,
//    '#size'  => 30,
//    '#maxlength' => 30,
//    '#default_value' => $new_person_node['email'],
//    // '#description' => t('Site name acronym'),
//  );
//
//
//  $form['old_persons'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Existing personnel data'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//  $form['old_persons']['first_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('first_name'),
//    '#default_value' => t('first_name'),
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );
//
//  $form['old_persons']['last_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('last_name'),
//    '#default_value' => t('last_name'),
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );
//
//  $form['old_persons']['email'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('email'),
//    '#default_value' => t('email'),
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );


  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}

//function personell_check_form_validate($form, &$form_state) {
//  foreach($form_state['values'] as $field_name => $value) {
//    if(strpos($field_name, 'node_') === 0) {
//      if(!is_numeric($value) || intval($value) < 0) {
//        form_set_error($field_name, t('Value must be a non-negative integer.'));
//      }
//    }
//  }
//}

function personell_check_form_submit($form, &$form_state) {
  drupal_set_message(t('The form has been submitted.'));
  $checked = array();

$a = $form_state['values'];
foreach ($a as $key => $value) {
//  dpm($value);
//  $k = 'node_17049';
/*
* if (preg_match("/(.+)=(.+)/", $code_definition['value'], $matches)) {
  views_bonus_eml_print_line('code',       $matches[1]);
  views_bonus_eml_print_line('definition', $matches[2]);
}
 */

  $e = preg_match("/node_(\d+)/", $key, $matches);
  $nid = $matches[1];
  if (preg_match("/node/", $key) AND $value == 1) {
    $checked[] = $nid;
//    dpm($nid);
  }
//  if (preg_match($pattern, $subject, $matches))
//  if (preg_match("/node/", $k) == 1) {
//   echo '$value - node';
//  }
//  else {
//   echo "Not Matched";
//  }
}
  variable_set('person_checked', $value);

//    dpm($checked);
//  $a = array_keys($form_state['values']);
//  $b = array_values($form_state['values']);

//  dpm($a);
//  dpm($b);
/*  TODO: get checked boxes and nids,
 * goto another form with full information
 *
 * values (Array, 9 elements)

    *
      node_16966 (Integer) 1
    *
      node_16887 (Integer) 1
    *
      node_16964 (Integer) 0
    *
      node_16965 (Integer) 0
    *
      node_16967 (Integer) 1
    *
      node_16887 (Integer) 0
    *
      node_16964 (Integer) 0
    *
      node_16965 (Integer) 0
    *
      node_16966 (Integer) 1
    *
      op (String, 6 characters ) Submit
    *
      submit (String, 6 characters ) Submit
    *
      form_build_id (String, 37 characters ) form-558943ef2d177d8eaad7beffcdb8fd8b
    *
      form_token (String, 32 characters ) 75fd1e0d33b939d51096f2fb342ba5b4
    *
      form_id (String, 20 characters ) personell_check_form | (Callback) personell_check_form();


*/

}

function personell_check_theme($existing, $type, $theme, $path) {
  return array(
    'personell_check_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}


function theme_personell_check_form_table($container) {

  // Define header row for the table
  $header = array(t('Nid'), t('First Name'), t('Last Name'), t('Email'), t('Compare'));

  $rows = array();

  foreach($container as $field_name => $field) {

    // All the fields were named 'node_' . $node->nid
    if (strpos($field_name, 'node_') === 0) {

      $nid = substr($field_name, 5);
      $node = node_load($nid);

      $rows[] = array(
        $node->nid,
        check_plain($node->field_person_first_name[0]['value']),
        check_plain($node->field_person_last_name[0]['value']),
        check_plain($node->field_person_email[0]['email']),
        drupal_render($field),
      );

    }
  }

  return theme_table($header, $rows);
}

//function personell_check_form_submit($form, &$form_state) {
//  drupal_set_message(t('The form has been submitted.'));
//}

function _get_new_person_node($new_person_nid) {
  $new_person = array();
  $node       = node_load($new_person_nid);
  $new_person['first_name'] = $node->field_person_first_name[0]['value'];
  $new_person['last_name']  = $node->field_person_last_name[0]['value'];
  $new_person['email']      = $node->field_person_email[0]['email'];

  return $new_person;
}


function _personell_check_items($old_person_nids) {
  $res = array();
  if ($old_person_nids) {
    foreach ($old_person_nids as $value) {
      $res[] = node_load($value);
    }
  }

  if (count($res) == 0) {
    drupal_set_message(t("Couldn't find any nodes!"), 'warning');
  }
  return $res;
}
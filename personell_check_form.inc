<?php

require_once('personell_check_form_submit.inc');

function personell_check_form($form_state) {
  $form = array();
  unset($last_settings);
//  TODO: rewrite!
  $new_person_nid = variable_get('new_person_nid', '1');

  $form['new_person'] = array(
    '#type' => 'fieldset',
    '#title' => t('New personnel data'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['new_person']['first_name'] = array(
    '#type'  => 'textfield',
    '#title' => t('First name'),
    // '#required'  => TRUE,
    '#size'  => 30,
    '#maxlength' => 30,
    '#default_value' => variable_get('new_person_nid', $new_person_nid),
    // '#description' => t('Site name acronym'),
  );

    $form['new_person']['last_name'] = array(
    '#type'  => 'textfield',
    '#title' => t('Last name'),
    // '#required'  => TRUE,
    '#size'  => 30,
    '#maxlength' => 30,
    '#default_value' => variable_get('new_person_nid', $new_person_nid),
    // '#description' => t('Site name acronym'),
  );

    $form['new_person']['email'] = array(
    '#type'  => 'textfield',
    '#title' => t('Email'),
    // '#required'  => TRUE,
    '#size'  => 30,
    '#maxlength' => 30,
    '#default_value' => variable_get('new_person_nid', $new_person_nid),
    // '#description' => t('Site name acronym'),
  );


  $form['old_persons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Existing personnel data'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['old_persons']['first_name'] = array (
    '#type'  => 'textfield',
    '#title' => t('first_name'),
    '#default_value' => t('first_name'),
    '#size'  => 60,
    '#maxlength' => 60,
  );

  $form['old_persons']['last_name'] = array (
    '#type'  => 'textfield',
    '#title' => t('last_name'),
    '#default_value' => t('last_name'),
    '#size'  => 60,
    '#maxlength' => 60,
  );

  $form['old_persons']['email'] = array (
    '#type'  => 'textfield',
    '#title' => t('email'),
    '#default_value' => t('email'),
    '#size'  => 60,
    '#maxlength' => 60,
  );


  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}            

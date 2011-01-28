<?php

require_once('personell_check_form_submit.inc');

function personell_check_form($form_state) {
  $form = array();
  unset($last_settings);
  $new_person_nid = variable_get('new_person_nid', '1');

  $form['new_person'] = array(
    '#type'  => 'textfield',
    '#title' => t('New person'),
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

    $form['old_persons']['organization'] = array (
    '#type'  => 'textfield',
    '#title' => t('organization'),
    '#default_value' => t('organization'),
    '#size'  => 60,
    '#maxlength' => 60,
    );
  
  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Submit'),
    );

  return $form;
}            

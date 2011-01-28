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

function person_subform($form, $role) {
  $states = array();

 $country_list = array ();

// If Metadata Provider exists take the last one and use by default
  $query = db_query('SELECT nid FROM content_type_person 
                      WHERE (field_person_role_value = "Metadata Provider" 
                        and nid = (SELECT max(nid) FROM content_type_person 
                                    WHERE field_person_role_value = "Metadata Provider"))');
          
  $metadata_provider_nid = db_result($query);
  if ($metadata_provider_nid) {
    $persion_node = node_load($metadata_provider_nid);
  }    
  // If Publisher exists take the last one and use by default
  if ($role == 'publisher') {
    $query = db_query('SELECT nid FROM content_type_person 
                        WHERE field_person_role_value = "Publisher" 
                          and nid = (SELECT max(nid) FROM content_type_person 
                                      WHERE field_person_role_value = "Publisher")');
    $publisher_nid = db_result($query);    
    
    if ($publisher_nid) {
      $persion_node = node_load($publisher_nid);
    }      
  }
  
  $form['persons'][$role] = array(
    '#type' => 'fieldset',
    '#title' => t($role_title),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['persons'][$role]['organization'] = array (
    '#type'  => 'textfield',
    '#title' => t('organization'),
    '#default_value' => variable_get('organization', $organization),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$role]['address'] = array (
    '#type'  => 'textfield',
    '#title' => t('address'),
    '#default_value' => variable_get('address', $address),
    '#size'  => 60,
    '#maxlength' => 100,
    );

  $form['persons'][$role]['city'] = array (
    '#type'  => 'textfield',
    '#title' => t('city'),
    '#default_value' => variable_get('city', $city),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$role]['state'] = array(
    '#type' => 'select',
    '#title' => t('state'),
    '#default_value' => variable_get('state', $state),
    '#options' => $states,
  );

  $form['persons'][$role]['zipcode'] = array (
    '#type'  => 'textfield',
    '#title' => t('zipcode'),
    '#default_value' => variable_get('zipcode', $zipcode),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$role]['country'] = array(
    '#type' => 'select',
    '#title' => t('country'),
    '#default_value' => variable_get('country', $country),
    '#options' => $country_list,
  );

  $form['persons'][$role]['phone'] = array (
    '#type'  => 'textfield',
    '#title' => t('phone'),
    '#default_value' => variable_get('phone', $phone),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$role]['fax'] = array (
    '#type'  => 'textfield',
    '#title' => t('fax'),
    '#default_value' => variable_get('fax', $fax),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$role]['role'] = array(
    '#type' => 'value',
    '#value' => $role_title,
  );

  $form['persons'][$role]['email'] = array (
    '#type'  => 'textfield',
    '#title' => t('email'),
    '#default_value' => variable_get('email', $email),
    // '#required'  => TRUE,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  // Commented fields are here in case we will need them

  // $form['persons'][$role]['first_name'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('first_name'),
  //   '#default_value' => variable_get('first_name', $first_name),
  //   '#size'  => 60,
  //   '#maxlength' => 60,
  //   );
  // 
  // $form['persons'][$role]['last_name'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('last_name'),
  //   '#default_value' => variable_get('last_name', $last_name),
  //   '#size'  => 60,
  //   '#maxlength' => 60,
  //   );

  // $form['persons'][$role]['personid'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('personid'),
  //   '#default_value' => variable_get('personid', $personid),
  //   '#size'  => 60,
  //   '#maxlength' => 60,
  //   );

  return $form;
}            

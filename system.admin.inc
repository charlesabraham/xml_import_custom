<?php



function xml_to_nodes(){


$content_type = variable_get('xml_migrate_bundle_selection', 'page');
$map_count = variable_get('xml_migrate_count','3');

$fields = field_info_instances("node", $content_type);


drupal_set_message("Bundle selected for mapping is '$content_type'",'status');
drupal_set_message("FIELD MAP count is $map_count.",'status');

foreach ($fields as $key => $value)
{
  $flist[$key] = $key;
}

for ($i = 1; $i <= $map_count; $i++)
{


$group_name = 'xml_migrate_group'.$i;

$xml_machine = 'xml_migrate_field_'.$i;

if(variable_get($xml_machine, ''))
{
$val = FALSE;
}else
{
$val = TRUE;
}


$form[$group_name] = array(
    '#type' => 'fieldset',
    '#title' => t('Field map '.$i),
    '#collapsible' => TRUE,
    '#collapsed' => $val,
  );

$xml_machine = 'xml_migrate_field_'.$i;

  $form[$group_name][$xml_machine] = array(
    '#type' => 'textfield',
    '#title' => t("Xml Field $i"),
    '#default_value' => variable_get($xml_machine, ''),
    '#size' => 15,
    '#description' => t("Custom variable field $i as per in the xml."),
  );

$drupal_machine = 'xml_migrate_field_drupal_'.$i;

  $form[$group_name][$drupal_machine] = array(
      '#type' => 'select',
      '#size' => 1,
      '#options' => $flist,
      '#multiple' => FALSE,
      '#title' => t("Drupal field $i"),
      '#default_value' => variable_get($drupal_machine, ''),
      '#description' => t('The Drupal cck field where the custom data in xml is to be mapped.'),
  );


}
return system_settings_form($form);
}


/**
 * Function to select the bundle.
 *
 */

function select_type(){

$ctype = node_type_get_types();

foreach ($ctype as $key => $value)
{
  $ctype_list[$key] = $value->name;
}


//$fields = field_info_instances("node", "services");

$group_name = 'xml_migrate_bundle';

$xml_machine = 'xml_migrate_bundle_selection';
$xml_machine2 = 'xml_migrate_count';

$form[$group_name] = array(
    '#type' => 'fieldset',
    '#title' => t('Bundle selection'),
    '#collapsible' => TRUE,

  );

  $form[$group_name][$xml_machine] = array(
    '#type' => 'select',
    '#size' => 1,
    '#options' => $ctype_list,
    '#multiple' => FALSE,
    '#title' => t("Content type"),
    '#default_value' => variable_get($xml_machine, ''),
    '#description' => t("Select the content type."),
  );

  $form[$group_name][$xml_machine2] = array(
    '#type' => 'textfield',
    '#size' => 2,
    '#title' => t("Mapping item count"),
    '#default_value' => variable_get($xml_machine2, '3'),
    '#description' => t("Enter the number of mapping fields."),
  );

return system_settings_form($form);
}

/**
 * File upload form
 *
 */

function xml_import_file_upload(){



$group_name = 'xml_migrate_file';

$xml_machine = 'xml_migrate_file_selection';

$form[$group_name] = array(
    '#type' => 'fieldset',
    '#title' => t('File Upload'),
    '#collapsible' => TRUE,
  );

  $form[$group_name][$xml_machine] = array(
        '#type' => 'managed_file',
        '#name' => 'xml_file',
        '#title' => t('Upload xml file, huh!'),
        '#default_value' => variable_get($xml_machine, ''),
        '#description' => t("Here you can upload an xml file to be imported!"),
        '#required' => TRUE,
        '#upload_location' => 'public://xlm_migrate_file/',
        '#upload_validators' => array(
            'file_validate_extensions' => array('xml'),
          ),
  );

  $form[$group_name]['#submit'][] = 'xml_import_set_default_header_image_form_submit';

return system_settings_form($form);

}

/*
 * Additional submit handler for making the file permanent
 */
function xml_import_set_default_header_image_form_submit($form, &$form_state){
  $form['xml_migrate_file_selection']['#file']->status = FILE_STATUS_PERMANENT;
  file_save($form['xml_migrate_file_selection']['#file']);
}

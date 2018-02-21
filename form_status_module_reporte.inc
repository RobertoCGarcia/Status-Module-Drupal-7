<?php

function form_status_module_reporte($form, &$form_state) {

     //$memcache_servers = variable_get('memcache_servers');
     //print " memcache_wildcard_flushes: " . print_r(variable_get('memcache_wildcard_flushes')) . "<br/>";
     //print " memcache_wildcard_invalidate: " . variable_get('memcache_wildcard_invalidate') . "<br/>";
     //print " cache_lifetime: " . variable_get('cache_lifetime') . "<br/>";         

     //Construir la lista de modulos guardada
     $modulesStoreFormat = variable_get('form_status_formNameList');
     $tmpList = explode("#=#" , $modulesStoreFormat);
     $lst = "";
     $tituloReporte = " Estatus de los Módulos "; 

     foreach($tmpList as $clave => $valor){
        if( strlen($valor) != 0 ){
           $lst .=  ($clave + 1) . ".- ". $valor . "<br/>";
           $listaModulos[$valor] = $valor;  
        }
     }
     
     $markup .= "<h1>" . $tituloReporte . "</h1>";

     $header = array(
         array('data' => t('Nombre del Módulos')),  
         array('data' => t(' ')), 
         array('data' => t('Tipo')),
         array('data' => t('Estatus')) 
     );

     $dataArray = array();
     foreach($listaModulos as $clave => $nombreModulo){
            
          $dataArray = form_status_info_module($nombreModulo);
          //$dataArray["count"]

          $statusModulo = ($dataArray["status"] == 1)?" Activado ":" Desactivado ";

          $rows[] = array(  array('data' => $dataArray["name"] ),  
                            array('data' => $dataArray["filename"] ),   
                            array('data' => $dataArray["type"] ),  
                            array('data' => $statusModulo),
                    );
     }

     $markup .= theme('table', array('header' => $header, 'rows'=> $rows));

     /**
      * Estatus de los Servidores de Varnish
     */
     
     $markup .= status_servers_varnish();

  return $markup;

}

function form_status_info_module($moduleName){
   
   $lstInfoModule = array();
   $q = "SELECT filename, name, type, status FROM {system} WHERE name = :moduleName";
   $result = db_query($q, array(':moduleName' => $moduleName))->fetchObject();

   $q = "SELECT filename, name, type, status FROM {system} WHERE name = :moduleName";
   $numRows = db_query($q, array(':moduleName' => $moduleName))->rowCount();
 
   $lstInfoModule["count"] = $numRows;
   $lstInfoModule["filename"] = $result->filename;
   $lstInfoModule["name"] = $result->name;
   $lstInfoModule["type"] = $result->type;
   $lstInfoModule["status"] = $result->status;
   
   return $lstInfoModule;

}


function status_servers_varnish() {

  $status = varnish_get_status();
  $statusServers = "";
  $txtStatus = "";
  foreach (varnish_get_status() as $ip => $status) {
       if($status == 1){
          $txtStatus = " <br/> Estatus: <div style='color:green' align='left'><b>Up</b></div> ";
       }else{
          $txtStatus = " <br/> Estatus: <div style='color:red' align='left'><b>Down</b></div> ";
       }
       $statusServers .=  " *IP Server ". $ip ."  " . $txtStatus . " <br/> ";
  }
 
 $statusServers;


 
  return $statusServers;
}
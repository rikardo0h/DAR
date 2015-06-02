<!DOCTYPE html>
<html>
<head id="Head1" runat="server">
    <meta charset="utf-8" />
    <title>Página de Inicio</title>
    <link href="Content/bootstrap.min.css" rel="stylesheet" />
    <link href="Content/Estilos.css" rel="stylesheet" />
    <link href="favicon.ico" rel="shortcut icon" type="image/x-icon" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style>
        body {
            background: url(/Imagenes/fondo0.jpg) no-repeat center top fixed;
            background-size: cover;
            -moz-background-size: cover;
            -webkit-background-size: cover;
            -o-background-size: cover;
        }
    </style>
</head>
<body>    
    <header>
        <div class="row-fluid">
            <div class="col-xs-12">
                <nav class="navbar  navbar-default barMenu" role="navigation">
                    <div class="container-fluid">
                        <div class="row logoMenu">
                            <img class="navbar-text navbar-left hidden-xs" src="Imagenes/Lu.png" width="200" />
                            <img class="navbar-text navbar-right hidden-xs logoSep" src="Imagenes/red.png" width="170" />
                            <h3 class="text-center" style="margin: 10px">Plataforma PAR</h3>
                            <h4 class="text-center" style="margin: -5px"><strong>PAR</strong> - <small>Snifer de red</small></h4>
                        </div>
                    </div>
                </nav>
            </div>
        </div>
    </header>
    <section>
        <div class="row-fluid formVal">
             <div class="col-lg-12">
                <form id="form1" runat="server" action="ejecutar">
                    <div class="input-group">                                             
                        <input class="form-control" ID="Cadena" name="Cadena" type="text" runat="server" placeholder="Escriba la Cadena Digital O Folio" />                            
                        <span class="input-group-btn">
                            <input type="submit" name="Validar" value="Validar" class="btn btn-default"/>
                        </span>                            
                    </div>                                       
                </form>
             </div>            
        </div>
    </section>            
</body>
</html>

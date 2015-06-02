using Plataforma_PAR.ServiceReference1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Script.Serialization;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Plataforma_PAR
{
    public partial class ip : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnIp_Click(object sender, EventArgs e)
        {
            //Código para escanear IPs
            ReceptorSoapClient x = new ReceptorSoapClient();
            String cadena = x.scanIPS();
            String[] res = cadena.Split(new String[]{"\n"},StringSplitOptions.None );
            txtIp.Text = res[0];
        }
    }
}
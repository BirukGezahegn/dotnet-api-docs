﻿// System.Web.Services.Protocols.LogicalMethodInfo.IsBeginMethod(MethodInfo)
// System.Web.Services.Protocols.LogicalMethodInfo.IsEndMethod(MethodInfo)

/*
The following example demonstrates 'IsBeginMethod' and 'IsEndMethod' methods of 'System.Web.Services.Protocols.LogicalMethodInfo' class. The type information of methods of Math web service is taken in a varible of type MethodInfo. Then 'IsBeginMethod' and 'IsEndMethod' is used to query on created MethodInfo variable to find whether the method is begin and end method for asynchronous invocation or not.
Note:  The below MyMath class is a proxy class generated by the Wsdl.exe utility for the Math Web Service. This class can be found in SoapHttpClientProtocol Class example also.
*/

using System;
using System.Reflection;
using System.Web.Services.Protocols;

public class IsBeginMethodClass
{
   public static void Main()
   {
// <Snippet1>
// <Snippet2>

      // Get the type for the proxy class MyMath Web service.
      // Note: The MyMath class is a proxy class generated by the Wsdl.exe
      // utility for the Math Web service. This class can also be found in
      // the SoapHttpClientProtocol class example.
      Type myType = typeof(MyMath.MyMath);

      MethodInfo myBeginMethod = myType.GetMethod("BeginAdd");
      MethodInfo myEndMethod = myType.GetMethod("EndAdd");
      MethodInfo myMethod = myType.GetMethod("Add");

      Console.WriteLine("Is 'BeginAdd' a Begin Method : " +
         LogicalMethodInfo.IsBeginMethod(myBeginMethod).ToString());
      Console.WriteLine("Is 'Add' a Begin Method : " +
         LogicalMethodInfo.IsBeginMethod(myMethod).ToString());
      Console.WriteLine("Is 'EndAdd' an End Method : " +
         LogicalMethodInfo.IsEndMethod(myEndMethod).ToString());

// </Snippet1>
// </Snippet2>
   }
}

// Automatically generated proxy class for Math Web service.
// This class can also be found in SoapHttpClientProtocol class example.
namespace MyMath
{
   using System.Diagnostics;
   using System.Xml.Serialization;
   using System;
   using System.Web.Services.Protocols;
   using System.Web.Services;

   [System.Web.Services.WebServiceBindingAttribute(Name="MyMathSoap",
      Namespace="http://tempuri.org/")]
   public class MyMath : System.Web.Services.Protocols.SoapHttpClientProtocol
   {
      public MyMath()
      {
         this.Url = "http://localhost/Math.asmx";
      }

      [System.Web.Services.Protocols.SoapDocumentMethodAttribute(
         "http://tempuri.org/Add",
         Use=System.Web.Services.Description.SoapBindingUse.Literal,
         ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
      public int Add(int x, int y)
      {
         object[] results = this.Invoke("Add", new object[] {x,y});
         return ((int)(results[0]));
      }

      public System.IAsyncResult BeginAdd(int x, int y,
         System.AsyncCallback callback, object asyncState)
      {
         return this.BeginInvoke("Add", new object[] {x,y}, callback, asyncState);
      }

      public int EndAdd(System.IAsyncResult asyncResult)
      {
         object[] results = this.EndInvoke(asyncResult);
         return ((int)(results[0]));
      }
   }
}

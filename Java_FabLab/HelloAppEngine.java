package com.gonevertical.server.FabLab;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;


@WebServlet(
    name = "HelloAppEngine",
    urlPatterns = {"/hello"}
)

public class HelloAppEngine extends HttpServlet {
	
  
  
  @Override
  public void doGet(HttpServletRequest request, HttpServletResponse response) 
     throws IOException, ServletException {
	  //this.getServletContext().getRequestDispatcher("/WEB-INF/bonjour.jsp").forward( request, response);
	  DatastoreService ds=DatastoreServiceFactory.getDatastoreService();
	 
	 String firstName=request.getParameter("fname")	;
	 String LasttName=request.getParameter("lname")	;
	 String adressemail=request.getParameter("mail")	;
	 

	
	 Date maDate = new Date();  
	  
	  
	  //Create an entity without identifier
	  
	  Entity e=new Entity("person");
	  e.setIndexedProperty("Date", maDate);
	  e.setIndexedProperty("FirstName",firstName);
	  e.setIndexedProperty("LastName", LasttName);
	  e.setIndexedProperty("key", LasttName);
	  ds.put(e);
	  
	  //Creating an identifier
	  
	  Entity user=new Entity("user",firstName);
	  user.setProperty("userid",firstName);
	  user.setProperty("FirstName",firstName);
	  user.setProperty("LastName", LasttName);
	  user.setProperty("Email",adressemail);
	  ds.put(user);

	  
	  
	PrintWriter oute = response.getWriter();
    response.setContentType("text/html");
    response.setCharacterEncoding("UTF-8");
    
    response.getWriter().print(firstName);
    //response.getWriter().print("\n Vous êtes le bienvenu \n");
   oute.println("<link rel=\"stylesheet\" href=\"NewFile.css\"/>");
   oute.println("<p1>Bonjouuur</p>");
   oute.println("<p>ça c'est la page n°4<a href=\"index.html\">Acceuil</a>") ;
    

  }
  public void doPost(HttpServletRequest request, HttpServletResponse response) 
		     throws IOException {
	  
  
  }
}
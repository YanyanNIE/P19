## JEE et Frameworks

1. Composants JEE

    Servlet, JSP

2. Conteneurs JEE

    Web Container, EJB Container

3. Connecteurs et Services JEE

    JDBC, JavaMail

4. Les avantages de l’utilisation des pages JSP par rapport à CGI, ASP et SSI

    - a. Performance, pas de nécessité d’avoir un interprète, possibilité d’utiliser les connecteurs JDBC, etc 
    - b. Portabilité
    - c. Utilisation dans des contextes réels

5. Sur quel patron d’architecture logicielle est construit React ?
    
    One-way reactive data flow

6. Citez 3 nouvelles balises HTML5 permettant d’introduire plus de sémantique dans les structures de page HTML

    nav, header, main, footer, aside, article, section

7. Considérons la commande suivante : `<jsp:setProperty property="*" name="user"/>`
    - A quoi sert-elle et où on la déclare ?
        
        La commande sert à setter toutes les propriétés d’un bean qui s’appelle « user » et on la déclare dans un JSP
    
    - Quel est son équivalent Java ?
        - Instanciation d’un bean par le constructeur() publique
        - set «attribute»(value) pour chaque propriété du bean
    
    - Qu’est-ce qu’il faut déclarer avant de cette action afin de l’utiliser correctement ? 
        Il faut déclarer le bean « user » : <jsp:useBean id="user" class="classDuBeanUser" scope="session" />

8. Considérons le message d’erreur de compilation suivant :

```
java.lang.ClassNotFoundException: com.mysql.jdbc.Driver
at org.apache.catalina.loader.WebappClassLoader.loadClass(WebappClassLoader.java:1713) at org.apache.catalina.loader.WebappClassLoader.loadClass(WebappClassLoader.java:1558)
```
![](review/jee-erreur-vf.png)

9. Quels sont les avantages de l’utilisation de servlets par rapport aux CGI ? Citez au moins trois.

10. Expliquer comment communiquent les servlets entre elles ou avec une page JSP ? 

11. Citer quelques objets implicites qui peuvent être utilisés en JSP. Expliquer le principe de cette utilisation. 

12. Quels sont les avantages et les inconvénients des Servlet JEE. Comment surmonter les inconvénients ?

13. Examinez le code suivant :

```xml
<servlet> 
    <servlet-name>HelloWorldServlet</servlet-name> 
    <servlet-class>mypkg.HelloServlet</servlet-class>
</servlet>
<servlet-mapping> 
    <servlet-name>HelloWorldServlet</servlet-name> 
    <url-pattern>/sayhello</url-pattern>
</servlet-mapping>
```

14. Expliquer comment démarrer la servlet depuis un navigateur et où le serveur va chercher les classes pour le démarrage ?

15. Expliquez la différence parmi la directive d’inclusion <%@ include...%> et le tag jsp <jsp :include...>. Dans quel moment ces deux éléments sont exécutés dans une page JSP et de quel façon ? 

16. Complétez le texte ci-dessous afin d’avoir une servlet qui retourne la session actuelle et compte combien de fois le site web à été accédé pendant la session actuelle ? 

```java
package mypkg;
import java.io.*;
import javax.servlet.*; import javax.servlet.http.*; import java.util.Date;

public class SessionServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException {
    // Définissez le type MIME du message de réponse
    ...................................................
    // Allouez un writer pour écrire le message de réponse dans le réseau 
    ....................................................

    // Retournez la session existante si elle existe. Créez une nouvelle session autrement. Utilisez un compteur (accessCount) pour compter combien de fois le site a été accédé pendant la session actuelle.
    .................................................... 
    .................................................... 
    ....................................................
    .................................................... 
    ....................................................
   
    try {
        out.println("<!DOCTYPE html>");
        out.println("<html>");
        out.println("<head><meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>"> 
        out.println("<title>Session Test Servlet</title></head><body>");
        out.println("<h2> Vous avez eu accès à ce site " + accessCount + " fois pendant cette session.</h2>"); 
        out.println("</body></html>");
        } finally {
        out.close(); }
    } 
}
```

17. Donnez une représentation graphique du model MVC, expliquez les fonctionnalités de chaque partie et décrivez-en l’implémentation JEE.

18. Donnez une représentation graphique de la structure d’un module web en JEE, et expliquez la position et le contenu de chaque répertoire. 

19. Quels sont les 5 types d’éléments qui peuvent être contenus dans une page JSP (à part les balises HTML) ?

20. Examinez le code suivant; Dans quel fichier est-il contenu? Comment utiliser le paramètre « annee » dans la servlet ? 


```xml
<servlet> 
    <servlet-name>...</servlet-name>
    <servlet-class>...</servlet-class> 
    <init-param>
        <param-name>annee</param-name>
        <param-value>2012</param-value> 
    </init-param>
    <load-on-startup>..</load-on-startup> 
</servlet>
```
21. Quels sont les commandes nécessaires pour récupérer un objet de la session ?

22. Montrez un exemple de déclaration et utilisation d’un JavaBean dans une page JSP.

23. A quoi sert web.xml ?

24. A quoi servent HttpServletRequest et HttpServletResponse ?

25. Comment fait une servlet pour accéder aux cookies positionnés chez le client web et pour en positionner d'autres?

26. Comment est structurée une page JSP ? Citer les parties principales.

27. Donner les éléments essentiels contenus dans un fichier web.xml.

28. Expliquer le processus de sérialisation en java.

29. Le modèle bean : pour chacune des affirmations suivantes précisez à côté si elle est correcte ou non.
    - Implémente l’interface java.io.Serializable
    - Fournit un constructeur public sans argument
    - Possède des propriétés qui peuvent être modifiées lors de son déploiement
    - Peut interroger une base de données
    - Peut écouter des événements

30. Faites un schéma des relations entre servlet, JSP et Bean.

31. Quel est l’intérêt d’une bibliothèque de tags JSTL ? 

32.  Quelle est la différence entre les méthodes jsp:forward et jsp:include? 

33. Listez 3 attributs principaux qui caractérisent un cookie.

34. A quoi sert un cookie HTTP ? 

35. Peut-on faire fonctionner les Sessions sans passer par les Cookies ? Expliquer. 

36. CGI : quels sont brièvement les avantages et les inconvénients; 

37. Expliquer les actions numérotées dans le schéma suivant.

![](review/jee-action-schema.png)

38. Expliquer la commande suivante : getServletContext().getRequestDispatcher(urlCible).forward(req,resp);

## Web Services

1. Donnez la structure du message SOAP pour invoquer le service ‹ajouter› sachant que lw WSDL contient les balises suivant:

    ```xml
    <message name="insertUserService">
        <part name="nom" type="xsd:string"/>
        <part name="mail" type="xsd:string"/>
    </message>
    .........
    <message name="ajouterUserService">
        <part name="nom" type="xsd:string"/>
    </message>
    .........
    <portType name="ajouterPortType">
        <operation name="ajouter">
            <input message="insertUserService"/>
            <output message="ajouterUserService"/>
        </operation>
        ..........
    </portType>

    ```
2. Dans un WSDL, quel est le rôle de l'élément <types>? Dans quel métalangage est-il écrit?

3. Quel(s) protocole(s) de communication est(sont) utilisé(s) par SOAP.
    HTTP

4. Donner le rôle d'un namespace dans XML.

5. Donnez le rôle d'une description WSDL.

6. Quelle est la solution utilisée pour découvrir et indiquer la disponnibilité d'un web service?

7. Quels sont les formats autorisés pour l’échange de données dans des services SOAP ?

8. Donnez une représentation graphique du schéma architectural de Java RMI et décrivez-en les composants. Quelle class Java faut-il étendre pour utiliser une « remote interface » ?

9. Considérons la partie suivante d’un fichier WSDL (calc.wsdl):
    - Expliquer le rôle de l’élément <types>. Quel langage doit être utilisé pour définir cet élément ?
    - Compléter les éléments manquant numérotés de (1) à (4).
    - Donner le prototype (entête) des opérations définies par ce WSDL. Justifiez votre réponse en utilisant le WSDL.

```xml
<definitions name="calc">
....
<types>
<schema targetNamespace="urn:calc">
... 
</schema>
</types>

<message name="addRequest"> 
    <part name="a" type="xsd:double"/> 
    <part name="b" type="xsd:double"/>
</message>

<message name="addResponse">
    <part name="result" type="xsd:double"/>
</message>

<message name="subRequest"> 
    <part name="a" type="xsd:double"/> 
    <part name="b" type="xsd:double"/>
</message>

<message name="subResponse">
    <part name="result" type="xsd:double"/> 
</message>

<portType name="calcPortType">
    <operation name="add"> 
        <input message="(1)"/> 
        <output message="(2)"/>
    </operation>
    <operation name="sub">
        <input message="(3)"/>
        <output message="(4)"/> 
    </operation>
</portType>
```

10. Quel élément est obligatoire dans une enveloppe SOAP?

11. A quoi sert un Header dans une enveloppe SOAP?

12. QuelleestladifférenceentreWSDLetSOAP?
    
## Socket

1. Qu’est que c’est un protocole de communication ? Est-ce que « les sockets » en font partie.

2. De quel moyen de communication réel peut être rapproché le fonctionnement d'un échange via le protocole UDP ? et le TCP ?

3. Donner les couches de l’architecture TCP/IP via un schéma. Situer les protocoles HTTP, DNS, TCP, UDP et IP dans le schéma.

4. Qu’est ce qu’une socket ? A quoi servent-elles ? Citer les deux types principaux de sockets ? 
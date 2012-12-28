<nftm "data/templates/row.tpl" include /><!DOCTYPE html>
<html lang="<nftm language />">
<head>
  <meta charset="utf-8" />
  <title><nftm title /></title>
  <link rel="stylesheet" href="<nftm dirCSS />main.css" type="text/css" />
</head>
<body id="index" class="home">
<h1>A good example</h1>
<p>All items that are not code are pushed on to the stack.</p>
<p>Code manipulates the stack. For example, the following</p>
<code><pre>
  &lt;nftm users />
</pre></code>
<p>Will push the value of the variable "users" on to the stack.
Let's assume that users was populated by the model using a query
like "SELECT NAME, AGE FROM TBL_USERS ORDER BY NAME" and that
the query returned ALICE,36 and BOB,42.</p>
<p>Let's also assume that the "simpleRow" function takes the
rowset from the top of the stack, formats it and places an
updated rowset back on the stack. We'll use this:</p>
<code><pre>
  &lt;tr>&lt;td>${row.name}&lt;/td>&lt;td>${row.age}&lt;/td>&lt;/tr>
</pre></code>
<p>For our formatting.</p>
<p>In our example, calling</p>
<code><pre>
  &lt;nftm users row />
</pre></code>
<p>Will leave the following on the top of the stack.</p>
<code><pre>
  &lt;tr>&lt;td>ALICE&lt;/td>&lt;td>36&lt;/td>&lt;/tr>
  &lt;tr>&lt;td>BOB&lt;/td>&lt;td>42&lt;/td>&lt;/tr>
</pre></code>
<table border=1>
<nftm users { <tr><td>${attr.name}</td><td>${attr.age}</td></tr> } />
</table>
<table border=1>
<nftm users row />
</table>
<ul>
<nftm aList { <b>${attr}</b> } { <li>${attr}</li> } />
</ul>
<ul>
<nftm aList boldList listItem />
</ul>
<table border=1>
<nftm users rowBlue,rowGreen />
</table>
</body>
</html>

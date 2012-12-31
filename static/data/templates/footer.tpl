<div id="footer">
<billy '/Users/mdhender/Software/xcode/static/static/static/data/templates/footer.left.tpl'  include />
<billy '/Users/mdhender/Software/xcode/static/static/static/data/templates/footer.right.tpl' include />
</div><!-- id="footer" -->


<!-- test { and } -->
<billy { />
<p>one</p>
<p>two</p>
<billy } bold />

<!-- test conditional inclusion
     condition IF whatToDoIfTRUE ELSE whatToDoIfFalse THEN
  -->
<p> <billy true  if 'pass' else 'fail' then /> </p>
<p> <billy false if 'fail' else 'pass' then /> </p>
<p>you should see the word "pass" twice in the paragraph above and not see the word "fail"</p>



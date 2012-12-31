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
     executeFlag can be
         true
         false
     boolean IF whatToDoIfTrue ELSE whatToDoIfFalse FI
     1. push the boolean on to the stack
     2. the IF word sets the executeFlag
        executeFlag is set to boolean
     3. read words until FI is found
        when ELSE
             executeFlag is set to !executeFlag
        when executeFlag is true
             execute word
     4. the FI word sets executeFlag to true
  -->
<p>
  <billy true      if 'pass' else 'fail' fi />
  <billy true  not if 'fail' else 'pass' fi />
  <billy false     if 'fail' else 'pass' fi />
  <billy false not if 'pass' else 'fail' fi />
</p>
<p>you should see the word "pass" four times in the paragraph above and not see the word "fail"</p>



lines = readlines("aoc.txt");

total = 0;
opts = optimoptions('intlinprog', 'Display', 'off');
for lineNum = 1:numel(lines)
   q = split(lines(lineNum));
   numButtons = q.size(1)-2;
   p = digitsPattern;
   buttonsStr = q(2:numButtons+1);
   jolts = str2double(extract(q(q.size(1)),p))';
   totalButtons = length(jolts);
   buttons = false(numButtons,totalButtons);
   for i = 1:numButtons
        inButton = str2double(extract(buttonsStr(i),p))';
        buttons(i,inButton+1) = true;
   end
   val = intlinprog(ones(numButtons,1),1:numButtons,[],[],double(buttons)',jolts',zeros(numButtons,1),[],opts);
   total = total + sum(val);
end

total
var event;
function trans(platform)
{
	platform.transform(100,100);
	
	return "Transformation complete";
}


function transC(c)
{
	c.setCSize(100,100);
	
	return "Transformation complete";
}

function raiseEvent(string)
{
	event = new Event(string);
	return "Raise event complete";
}

function handleE(eh)
{
	eh.onEvent(event);
	return "Handle event complete";
}
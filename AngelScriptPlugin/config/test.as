// Funcdefs for callbacks
funcdef void UpdateFrameCallback(const Core::UpdateFrameMessage&in);

// Listeners
Core::MessageListener<Core::UpdateFrameMessage>@ update_frame_listener;

// Senders
Core::MessageSender<Utils::LogMessage>@ log_message_sender;

std::string module_name;

// Utils types
enum LogSeverity
{
	NONE = 0,
	ERROR = 1,
	WARNING = 2,
	INFO = 3,
	DEBUG = 4
}

void init(const std::string &in name)
{
	module_name = name;
	
	@log_message_sender = Core::MessageSender<Utils::LogMessage>(name, engine_context);
	
	@update_frame_listener = Core::MessageListener<Core::UpdateFrameMessage>(name);

	UpdateFrameCallback @cb = @onUpdateFrame;
	update_frame_listener.setMessageProcessingCallback(cb);
	update_frame_listener.registerAtDispatcher();
}

void shutdown()
{
	update_frame_listener.unregisterAtDispatcher();
}

int counter = 0;

void onUpdateFrame(const Core::UpdateFrameMessage&in msg)
{
	if(log_message_sender is null)
	{
		print("Sender is null");
		return;
	}
	if(counter > 1000)
    {
		Utils::LogMessage mesg;
		mesg.sender_info = module_name;
		mesg.severity = INFO;
		mesg.log_entry = "Heartbeat";
		
		log_message_sender.sendMessage(mesg);
		counter = 0;
    }
    counter++;	
}

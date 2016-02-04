class MockMinecraft:
    def __init__(self):
        print("Created MockMinecraft")
        
    def postToChat(self, msg):
        print("[Minecraft Chat]: " + msg)

def create():
    return MockMinecraft()